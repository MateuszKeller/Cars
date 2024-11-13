// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryLayout.h"

#include "UIManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UPrimaryLayout* UPrimaryLayout::GetPrimaryGameLayoutForPrimaryPlayer(const UObject* WorldContextObject)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	APlayerController* PlayerController = GameInstance->GetPrimaryPlayerController(false);
	return GetPrimaryGameLayout(PlayerController);
}

UPrimaryLayout* UPrimaryLayout::GetPrimaryGameLayout(const APlayerController* PlayerController)
{
	return PlayerController ? GetPrimaryGameLayout(PlayerController->GetLocalPlayer()) : nullptr;
}

UPrimaryLayout* UPrimaryLayout::GetPrimaryGameLayout(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer)
	{
		if (const UGameInstance* GameInstance = LocalPlayer->GetGameInstance())
		{
			if (UUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UUIManagerSubsystem>())
			{
				return UIManager->Layout;
			}
		}
	}

	return nullptr;
}

void UPrimaryLayout::FindAndRemoveWidgetFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	// We're not sure what layer the widget is on so go searching.
	for (const TTuple<EUILayoutLayer, TObjectPtr<UCommonActivatableWidgetContainerBase>>& Tuple : Layers)
	{
		Tuple.Value->RemoveWidget(*ActivatableWidget);
	}
}

UCommonActivatableWidgetContainerBase* UPrimaryLayout::GetLayerWidget(EUILayoutLayer LayerType)
{
	if(TObjectPtr<UCommonActivatableWidgetContainerBase>* Layer = Layers.Find(LayerType))
	{
		return *Layer;
	}

	return nullptr;
}

void UPrimaryLayout::RegisterLayer(EUILayoutLayer Mode, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->SetTransitionDuration(0.0);
		Layers.Add(Mode, LayerWidget);
	}
}


/// UAsyncAction_PushContentToLayerForPlayer ///

UAsyncAction_PushContentToLayerForPlayer::UAsyncAction_PushContentToLayerForPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAsyncAction_PushContentToLayerForPlayer* UAsyncAction_PushContentToLayerForPlayer::PushContentToLayerForPlayer(APlayerController* InOwningPlayer, TSoftClassPtr<UCommonActivatableWidget> InWidgetClass, EUILayoutLayer InLayerMode, bool bSuspendInputUntilComplete)
{
	if (InWidgetClass.IsNull())
	{
		FFrame::KismetExecutionMessage(TEXT("PushContentToLayerForPlayer was passed a null WidgetClass"), ELogVerbosity::Error);
		return nullptr;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(InOwningPlayer, EGetWorldErrorMode::LogAndReturnNull))
	{
		UAsyncAction_PushContentToLayerForPlayer* Action = NewObject<UAsyncAction_PushContentToLayerForPlayer>();
		Action->WidgetClass = InWidgetClass;
		Action->OwningPlayerPtr = InOwningPlayer;
		Action->LayerMode = InLayerMode;
		Action->bSuspendInputUntilComplete = bSuspendInputUntilComplete;
		Action->RegisterWithGameInstance(World);

		return Action;
	}

	return nullptr;
}

void UAsyncAction_PushContentToLayerForPlayer::Cancel()
{
	Super::Cancel();

	if (StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
}

void UAsyncAction_PushContentToLayerForPlayer::Activate()
{
	if (UPrimaryLayout* RootLayout = UPrimaryLayout::GetPrimaryGameLayout(OwningPlayerPtr.Get()))
	{
		TWeakObjectPtr<UAsyncAction_PushContentToLayerForPlayer> WeakThis = this;
		StreamingHandle = RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(LayerMode, bSuspendInputUntilComplete, WidgetClass, [this, WeakThis](EAsyncWidgetLayerState State, UCommonActivatableWidget* Widget)
		{
			if (WeakThis.IsValid())
			{
				switch (State)
				{
					case EAsyncWidgetLayerState::Initialize:
						BeforePush.Broadcast(Widget);
						break;
					case EAsyncWidgetLayerState::AfterPush:
						AfterPush.Broadcast(Widget);
						SetReadyToDestroy();
						break;
					case EAsyncWidgetLayerState::Canceled:
						SetReadyToDestroy();
						break;
				}
			}
			SetReadyToDestroy();
		});
	}
	else
	{
		SetReadyToDestroy();
	}
}
