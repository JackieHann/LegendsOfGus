// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Styling/SlateColor.h"
#include "BaseController.generated.h"

/**
 * 
 */

class AInteractableObject;

UCLASS()
class MYPROJECT2_API ABaseController : public APlayerController
{
	GENERATED_BODY()
	ABaseController();

public:

	//Interactable Functions
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool GetInteractableWidgetEnabled();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FVector2D GetInteractableScreenspaceCoord();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FString GetInteractableString();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FSlateColor GetInteractableColour();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetTargetInteractable(AInteractableObject* obj);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool HasTargetInteractable();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AInteractableObject* GetTargetInteractable();


	FVector GetPlayerWorldPos();

private:
	AInteractableObject* m_targetted_interactable;
};
