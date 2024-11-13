// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerSubsystem.h"

#include "PrimaryLayout.h"
#include "Framework/Application/NavigationConfig.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

DEFINE_LOG_CATEGORY(UIManagerSubsystemLog);

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const TSharedRef<FNavigationConfig> Navigation = MakeShared<FNavigationConfig>();
	Navigation->bKeyNavigation = true;
	Navigation->bTabNavigation = false;
	Navigation->bAnalogNavigation = true;
	FSlateApplication::Get().SetNavigationConfig(Navigation);
}

bool UUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	TArray<UClass*> ChildClasses;
	GetDerivedClasses(GetClass(), ChildClasses, false);

	// Only create an instance if there is no override implementation defined elsewhere
	return ChildClasses.Num() == 0;
}


void UUIManagerSubsystem::CreateLayoutWidget(APlayerController* PlayerController, TSubclassOf<UPrimaryLayout> Class)
{
	if (ensure(PlayerController))
	{
		if (ensure(Class))
		{
			Layout = CreateWidget<UPrimaryLayout>(PlayerController, Class);
			
			UE_LOG(UIManagerSubsystemLog, Log, TEXT("Adding player [%s]'s root layout [%s] to the viewport"), *GetNameSafe(PlayerController), *GetNameSafe(Layout));

			Layout->SetPlayerContext(FLocalPlayerContext(PlayerController->GetLocalPlayer()));
			Layout->AddToPlayerScreen(1000);

#if WITH_EDITOR
			if (GIsEditor && PlayerController->GetLocalPlayer()->IsPrimaryPlayer())
			{
				// So our controller will work in PIE without needing to click in the viewport
				FSlateApplication::Get().SetUserFocusToGameViewport(0);
			}
#endif
		}
	}
}

bool UUIManagerSubsystem::IsLayerActive(EUILayoutLayer Layer)
{
	if(!IsValid(Layout))
	{
		return false;
	}

	if(UCommonActivatableWidgetContainerBase* LayerWidget = Layout->GetLayerWidget(Layer))
	{
		return IsValid(LayerWidget->GetActiveWidget());
	}

	return false;
}