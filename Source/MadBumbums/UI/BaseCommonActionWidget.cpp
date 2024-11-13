// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCommonActionWidget.h"
#include "CommonInputSubsystem.h"
#include "CommonUITypes.h"
#include "EnhancedInputSubsystems.h"

void UBaseCommonActivatableWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseCommonActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

UBaseCommonActivatableWidget::UBaseCommonActivatableWidget(const FObjectInitializer& ObjectInitializer)
{
	
}

void UBaseCommonActivatableWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (CommonUI::IsEnhancedInputSupportEnabled() && InputMapping)
	{
		if (const ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				FModifyContextOptions Options;
				Options.bForceImmediately = true;
				Options.bIgnoreAllPressedKeysUntilRelease = true;
				InputSystem->AddMappingContext(InputMapping, InputMappingPriority, Options);
			}
		}
	}
// TODO: DELETE IF WORKING ON NEWER UNREAL VERSIONS
	if (const UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
	{
		CommonInputSubsystem->OnInputMethodChangedNative.Broadcast(CommonInputSubsystem->GetCurrentInputType());
	}
}

void UBaseCommonActivatableWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
}

void UBaseCommonActivatableWidget::NativeDestruct()
{
	Super::NativeDestruct();

	OnWidgetDestroyed.Broadcast();
	ClearCurrentDesiredFocusTarget();
}

UWidget* UBaseCommonActivatableWidget::NativeGetDesiredFocusTarget() const
{
	if(UWidget* DesiredFocusTarget = BP_GetDesiredFocusTarget())
	{
		return DesiredFocusTarget;
	}
	
	return IsValid(CurrentDesiredFocusTarget) ? CurrentDesiredFocusTarget : DefaultDesiredFocusTarget;
}

void UBaseCommonActivatableWidget::GetDesiredInputConfigDirect(ECommonInputMode& OutInputMode, EMouseCaptureMode& OutMouseCaptureMode)
{
	const FUIInputConfig Config = GetDesiredInputConfig().GetValue();
	OutInputMode = Config.GetInputMode();
	OutMouseCaptureMode = Config.GetMouseCaptureMode();
}

TOptional<FUIInputConfig> UBaseCommonActivatableWidget::GetDesiredInputConfig() const
{
	if(bCustomInputMode)
	{
		return FUIInputConfig(InputMode, MouseCaptureMode);
	}
	
	switch (UIInputMode)
	{
	case EUIInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
		
	case EUIInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		
	case EUIInputMode::GameMenu:
		return FUIInputConfig(ECommonInputMode::All, MouseCaptureMode);
		
	default:
		return TOptional<FUIInputConfig>();
	}	
}

bool UBaseCommonActivatableWidget::BP_RegisterScrollRecipient(UWidget* WidgetToRegister)
{
	if(ensureAlwaysMsgf(IsValid(WidgetToRegister), TEXT("No Widget to Register as Scroll Recipient!")))
	{
		RegisterScrollRecipient(*WidgetToRegister);
		return true;
	}
	return false;
}

bool UBaseCommonActivatableWidget::BP_UnregisterScrollRecipient(UWidget* WidgetToUnregister)
{
	if(ensureAlwaysMsgf(IsValid(WidgetToUnregister), TEXT("No Widget to Unregister as Scroll Recipient!")))
	{
		UnregisterScrollRecipient(*WidgetToUnregister);
		return true;
	}
	return false;
}

void UBaseCommonActivatableWidget::UnregisterAllScrollRecipients()
{
	for(TWeakObjectPtr<const UWidget> ScrollRecipient : GetScrollRecipients())
	{
		UnregisterScrollRecipient(*ScrollRecipient);
	}
}

void UBaseCommonActivatableWidget::UpdateCurrentDesiredFocusTarget(UWidget* InWidget)
{
	CurrentDesiredFocusTarget = InWidget;
}

void UBaseCommonActivatableWidget::ClearCurrentDesiredFocusTarget()
{
	CurrentDesiredFocusTarget = nullptr;
}

void UBaseCommonActivatableWidget::UpdateInputMode(EUIInputMode InInputMode)
{
	UIInputMode = InInputMode;
}
