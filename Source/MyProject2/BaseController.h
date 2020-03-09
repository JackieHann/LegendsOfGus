// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InteractableObject.h"
#include "BaseController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API ABaseController : public APlayerController
{
	GENERATED_BODY()
	ABaseController();

public:

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetTargetInteractable(AInteractableObject* obj);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool HasTargetInteractable();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AInteractableObject* GetTargetInteractable();
private:
	AInteractableObject* m_targetted_interactable;
};
