// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManualLootObject.h"
#include "DifficultyInteractionObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API ADifficultyInteractionObject : public AManualLootObject
{
	GENERATED_BODY()
	
public:
	
	virtual void Interact(ABaseController* controller) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ADifficultyInteractionObject();

	UPROPERTY(EditDefaultsOnly)
		bool Increases_Difficulty;


};
