// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManualLootObject.h"
#include "PortalInteractionObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API APortalInteractionObject : public AManualLootObject
{
	GENERATED_BODY()
	
public:

	APortalInteractionObject();

	virtual void Interact(ABaseController* controller) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString GetInteractText() override;

private:
	

	UPROPERTY(EditDefaultsOnly)
	FVector Target_World_Position;

	UPROPERTY(EditDefaultsOnly)
	bool Is_Start_Dungeon_Spawn;
};
