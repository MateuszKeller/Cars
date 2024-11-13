// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputCoreTypes.h"

class UInputAction;
/**
 * 
 */
class MADBUMBUMS_API UILayoutFunctionLibrary  : public UBlueprintFunctionLibrary
{

public:

	UFUNCTION(BlueprintCallable)
	static void GetKeysFromDataHandle(const FDataTableRowHandle& Handle, FKey& KeyboardKey, FKey& GamepadKey);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static ULocalPlayer* GetLocalPlayerFromController(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static FName SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason);

	static FName SuspendInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendReason);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static void ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken);

	static void ResumeInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendToken);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "CommonUI")
	static TArray<FKey> GetEnhancedInputActionKeys(const ULocalPlayer* LocalPlayer, const UInputAction* InputAction);

private:
	
	static int32 InputSuspensions;
};
