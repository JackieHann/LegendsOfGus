// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "BaseController.h"
#include "BasicLootObject.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT2_API ABasicLootObject : public AInteractableObject
{
	GENERATED_BODY()

public:
	void Interact(ABaseController* controller);
};
