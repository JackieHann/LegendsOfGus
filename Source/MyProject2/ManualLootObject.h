// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "BaseController.h"
#include "ManualLootObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AManualLootObject : public AInteractableObject
{
	GENERATED_BODY()

public:
	virtual void Interact(ABaseController* controller) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool OverridesDeletion();

	virtual void DeleteSelf();
};
