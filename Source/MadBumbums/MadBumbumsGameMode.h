// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MadBumbumsGameMode.generated.h"

UCLASS(MinimalAPI)
class AMadBumbumsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMadBumbumsGameMode();

	UFUNCTION(BlueprintCallable)
	void RegisterAsFollowTarget(AActor* Requester);

	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Runtime")
	TObjectPtr<AActor> FollowTarget;
};



