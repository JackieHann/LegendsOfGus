// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CombatCharacter.h"
#include "Components/SphereComponent.h"
#include "InteractableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AInteractableCharacter : public ACombatCharacter
{
	GENERATED_BODY()

	//Vars
public:
	/** Loot Collider for Radial Loot Pickup **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* m_loot_collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	int m_manual_loot_dist = 400;

	//Functs
public:
	// Sets default values for this character's properties
	AInteractableCharacter();

	virtual void Tick(float delta_time) override;

private:
	void UpdateManualPickup();
	void UpdateAutomaticPickup();
	
};
