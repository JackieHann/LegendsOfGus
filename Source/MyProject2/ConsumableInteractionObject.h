// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManualLootObject.h"
#include "ConsumableInteractionObject.generated.h"

/**
 * Interaction class that 
 */
UCLASS()
class MYPROJECT2_API AConsumableInteractionObject : public AManualLootObject
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();
	virtual void Interact(ABaseController* controller) override;
	virtual bool OverridesDeletion() override;

	virtual FString GetInteractText() override;
protected:

	AConsumableInteractionObject();
	void Consume(ABaseController* controller);

	UPROPERTY(EditDefaultsOnly)
	int Charges;

	UPROPERTY(EditDefaultsOnly)
	int Health_Restored;

	UPROPERTY(EditDefaultsOnly)
	bool Destroy_On_Consume;

	UPROPERTY(EditDefaultsOnly)
	bool Show_Charges_UI;
	
	int current_charges;

	
};
