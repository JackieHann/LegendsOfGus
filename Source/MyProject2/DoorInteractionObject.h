// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManualLootObject.h"
#include "BaseController.h"
#include "DoorInteractionObject.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT2_API ADoorInteractionObject : public AManualLootObject
{
	GENERATED_BODY()

public:
	void Interact(ABaseController* controller);

	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	ADoorInteractionObject();
	float originalRotation;

	bool Opening;
	bool Closing;
	bool isClosed;

	float DotP;
	float MaxDegree;
	float AddRotation;
	float PosNeg;
	float DoorCurrentRotation;

};
