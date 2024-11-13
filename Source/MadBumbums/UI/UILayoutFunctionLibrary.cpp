// Fill out your copyright notice in the Description page of Project Settings.


#include "UILayoutFunctionLibrary.h"
#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "CommonUITypes.h"

int32 UILayoutFunctionLibrary::InputSuspensions = 0;

void UILayoutFunctionLibrary::GetKeysFromDataHandle(const FDataTableRowHandle& Handle, FKey& KeyboardKey, FKey& GamepadKey)
{
	KeyboardKey	= CommonUI::GetInputActionData(Handle)->GetInputTypeInfo(ECommonInputType::MouseAndKeyboard, FCommonInputDefaults::GamepadGeneric).GetKey();
	GamepadKey	= CommonUI::GetInputActionData(Handle)->GetInputTypeInfo(ECommonInputType::Gamepad, FCommonInputDefaults::GamepadGeneric).GetKey();
}

ULocalPlayer* UILayoutFunctionLibrary::GetLocalPlayerFromController(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		return Cast<ULocalPlayer>(PlayerController->Player);
	}

	return nullptr;
}

FName UILayoutFunctionLibrary::SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason)
{
	return SuspendInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendReason);
}

FName UILayoutFunctionLibrary::SuspendInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendReason)
{
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		InputSuspensions++;
		FName SuspendToken = SuspendReason;
		SuspendToken.SetNumber(InputSuspensions);

		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, true);

		return SuspendToken;
	}

	return NAME_None;
}

void UILayoutFunctionLibrary::ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken)
{
	ResumeInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendToken);
}

void UILayoutFunctionLibrary::ResumeInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendToken)
{
	if (SuspendToken == NAME_None)
	{
		return;
	}

	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, false);
	}
}

TArray<FKey> UILayoutFunctionLibrary::GetEnhancedInputActionKeys(const ULocalPlayer* LocalPlayer, const UInputAction* InputAction)
{
	TArray<FKey> OutKeys;
	CommonUI::GetEnhancedInputActionKeys(LocalPlayer, InputAction, OutKeys);
	return OutKeys;
}

