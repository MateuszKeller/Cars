// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManagerSubsystem.generated.h"

enum class EUILayoutLayer : uint8;
class UPrimaryLayout;

DECLARE_LOG_CATEGORY_EXTERN(UIManagerSubsystemLog, Log, All);

/**
 * 
 */
UCLASS()
class MADBUMBUMS_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	
	UFUNCTION(BlueprintCallable)
	void CreateLayoutWidget(APlayerController* PlayerController, TSubclassOf<UPrimaryLayout> Class);

	UFUNCTION(BlueprintCallable)
	bool IsLayerActive(EUILayoutLayer Layer);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPrimaryLayout> Layout;
};
