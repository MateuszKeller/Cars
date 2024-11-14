// Copyright Epic Games, Inc. All Rights Reserved.

#include "MadBumbumsGameMode.h"
#include "MadBumbumsPlayerController.h"

AMadBumbumsGameMode::AMadBumbumsGameMode()
{
	PlayerControllerClass = AMadBumbumsPlayerController::StaticClass();
}

void AMadBumbumsGameMode::RegisterAsFollowTarget(AActor* Requester)
{
	FollowTarget = Requester; 
}
