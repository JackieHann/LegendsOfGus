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

	enum LootRarity
	{
		LR_COMMON,
		LR_UNCOMMON,
		LR_RARE,
		LR_EPIC,
		LR_LEGENDARY
	};
	

	struct PlayerLootInfo
	{
		int loot_count[LR_LEGENDARY+1];
	} m_player_loot_info;

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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnPlayerDeath();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnPlayerWin();

	//UFUNCTION(BlueprintCallable)
	//void GetPlayer;

	UFUNCTION(BlueprintCallable)
	int GetPlayerLootCount(int rarity);

	UFUNCTION(BlueprintCallable)
	void AddPlayerLootCount(int rarity);

	UFUNCTION(BlueprintCallable)
	void DecrementPlayerLootCount(int rarity);

	virtual void Tick(float delta_time) override;

	//UPROPERTY(EditDefaultsOnly)
	float player_difficulty = 1;

	UFUNCTION(BlueprintCallable)
	void ChangeDifficulty(int num);

	UFUNCTION(BlueprintCallable)
	int GetDifficulty();


	UFUNCTION(BlueprintCallable)
	float GetDifficultyModifier();


	UFUNCTION(BlueprintCallable)
	int GetTotalScore();

	UFUNCTION(BlueprintCallable)
	FString GetStateAsText();

	void SetWon();

private:

	bool has_won = false;

	float timer = 0.0f;
	bool should_update_score = false;
	int m_total_score = 0;
	void UpdateTotalScore();

	int m_current_keys = 0;
	
	float player_current_health = 100;
	float player_lerping_health = 100;

	void ClampPlayerHealth();
};
