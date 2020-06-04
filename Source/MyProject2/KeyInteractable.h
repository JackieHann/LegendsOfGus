// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManualLootObject.h"
#include "KeyInteractable.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AKeyInteractable : public AManualLootObject
{
	GENERATED_BODY()
public:
	virtual void BeginPlay();
	virtual void Interact(ABaseController* controller) override;

private:

};
