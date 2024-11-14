// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BumAIController.generated.h"

/**
 * 
 */
UCLASS()
class MADBUMBUMS_API ABumAIController : public AAIController
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;
	
public:
	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Runtime")
	TObjectPtr<AActor> ActorToFollow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Runtime")
	FName BBFollowValueName;
	
};
