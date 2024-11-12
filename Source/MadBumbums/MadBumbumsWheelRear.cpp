// Copyright Epic Games, Inc. All Rights Reserved.

#include "MadBumbumsWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UMadBumbumsWheelRear::UMadBumbumsWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}