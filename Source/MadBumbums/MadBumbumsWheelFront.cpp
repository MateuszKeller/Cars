// Copyright Epic Games, Inc. All Rights Reserved.

#include "MadBumbumsWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UMadBumbumsWheelFront::UMadBumbumsWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}