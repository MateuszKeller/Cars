// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MadBumbumsPawn.h"
#include "MadBumbumsSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class MADBUMBUMS_API AMadBumbumsSportsCar : public AMadBumbumsPawn
{
	GENERATED_BODY()
	
public:

	AMadBumbumsSportsCar();
};
