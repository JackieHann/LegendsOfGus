// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MovableCharacter.h"
#include "CombatCharacter.generated.h"

UCLASS()
class MYPROJECT2_API ACombatCharacter : public AMovableCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void decreasePlayerHealth(float damage_amount);
};
