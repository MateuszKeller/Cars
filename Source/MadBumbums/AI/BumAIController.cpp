// Fill out your copyright notice in the Description page of Project Settings.


#include "BumAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MadBumbums/MadBumbumsGameMode.h"
#include "MadBumbums/Interfaces/LocationForAIInterface.h"

void ABumAIController::BeginPlay()
{
	Super::BeginPlay();

	if(const AMadBumbumsGameMode* GM = Cast<AMadBumbumsGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ActorToFollow = GM->FollowTarget;
	}

	GetBlackboardComponent()->SetValueAsObject(BBFollowValueName, ActorToFollow);
	
}

void ABumAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!ActorToFollow || !ActorToFollow->Implements<ULocationForAIInterface>())
	{
		return;
	}

	const FVector LocationToFollow = ILocationForAIInterface::Execute_GetSteerLocationForAI(ActorToFollow, GetPawn());

#if WITH_EDITOR
	UKismetSystemLibrary::DrawDebugPoint(this, LocationToFollow, 5.f, FColor::Magenta, 0.5f);
#endif 
}
