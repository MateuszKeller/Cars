// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LocationForAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULocationForAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MADBUMBUMS_API ILocationForAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector GetSpeedLocationForAI(AActor* Requester);
	virtual FVector GetSpeedLocationForAI_Implementation(AActor* Requester) = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector GetSteerLocationForAI(AActor* Requester);
	virtual FVector GetSteerLocationForAI_Implementation(AActor* Requester) = 0;
};
