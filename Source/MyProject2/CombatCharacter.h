// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
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

	UPROPERTY(EditDefaultsOnly)
	float player_max_health = 100;


	UFUNCTION(BlueprintCallable)
	void decreasePlayerHealth(float damage_amount);

	UFUNCTION(BlueprintCallable)
	void increasePlayerHealth(float health_gained);

	UFUNCTION(BlueprintCallable)
	float GetPlayerCurrentHealth();

	UFUNCTION(BlueprintCallable)
	float GetPlayerMaxHealth();

	UFUNCTION(BlueprintCallable)
	float GetPlayerHealthPercentage();

	UFUNCTION(BlueprintCallable)
	float GetPlayerLerpingHealthPercentage();

	virtual void Tick(float delta_time) override;

private:

	int m_current_keys;
	
	float player_current_health = 100;
	float player_lerping_health = 100;

	void ClampPlayerHealth();
};
