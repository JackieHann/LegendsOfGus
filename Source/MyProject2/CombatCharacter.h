// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MovableCharacter.h"
#include "CombatCharacter.generated.h"

//REPURPOSED TO HOLD PLAYER CHARACTER INFORMATION
//AUsefulCharacter
UCLASS()
class MYPROJECT2_API ACombatCharacter : public AMovableCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();


	bool HasKey();
	void UseKey();
	void AddKey(int amt);
private:
	int m_current_keys;
};
