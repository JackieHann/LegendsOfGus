// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BaseController.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MYPROJECT2_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	/*
		Variables
		- Any private variables that help with visibility etc.
	*/

	/*
		Functions
		- Any private functions not usable by blueprints
	*/

	void SetUIVisibility(ESlateVisibility visible);
	void UpdateUI(ABaseController* const player_controller);

public:

	//Overrides
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	/*  ELEMENTS
		- Any specific element we want to change at runtime must be defined as below
	    - Binds a widget's propertys to a variable of the same name
	*/

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* HeaderText = nullptr;	

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UHorizontalBox* Root = nullptr;
};
