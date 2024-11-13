// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseCommonActionWidget.generated.h"


UENUM(BlueprintType)
enum class EUIInputMode : uint8
{
	Game,
	Menu,
	GameMenu
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetDestroyed);

/**
 * 
 */
UCLASS()
class MADBUMBUMS_API UBaseCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

	public:

	UPROPERTY(BlueprintAssignable)
	FOnWidgetDestroyed OnWidgetDestroyed;


	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	
	UBaseCommonActivatableWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual void NativeDestruct() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
		
	
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Desired Input Config")
	void GetDesiredInputConfigDirect(ECommonInputMode& InputMode, EMouseCaptureMode& MouseCaptureMode);
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

	
	UFUNCTION(BlueprintCallable, DisplayName = "Register Scroll Recipient")
	bool BP_RegisterScrollRecipient(UWidget* WidgetToRegister);
	UFUNCTION(BlueprintCallable, DisplayName = "Unregister Scroll Recipient")
	bool BP_UnregisterScrollRecipient(UWidget* WidgetToUnregister);
	UFUNCTION(BlueprintCallable)
	void UnregisterAllScrollRecipients();
	
	UFUNCTION(BlueprintCallable)
	void UpdateCurrentDesiredFocusTarget(UWidget* InWidget);
	UFUNCTION(BlueprintCallable)
	void ClearCurrentDesiredFocusTarget();

	UFUNCTION(BlueprintCallable)
	void UpdateInputMode(EUIInputMode InInputMode);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	UWidget* CurrentDesiredFocusTarget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UWidget* DefaultDesiredFocusTarget;

	
protected:

	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	bool bCustomInputMode = false;
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (EditCondition = "bCustomInputMode==false"))
	EUIInputMode UIInputMode = EUIInputMode::Menu;
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (EditConditionHides, EditCondition = "bCustomInputMode==true"))
	ECommonInputMode InputMode;
	/** The desired mouse behavior when the game gets input. */
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (EditConditionHides, EditCondition = "bCustomInputMode==true || UIInputMode==EUIInputMode::GameMenu"))
	EMouseCaptureMode MouseCaptureMode;
	
};
