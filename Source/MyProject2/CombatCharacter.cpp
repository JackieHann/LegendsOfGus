// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"
#include "Enemy.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Called Combat Actor Constructor.."));

	player_current_health = player_max_health;
	m_current_keys = 0;
}


int ACombatCharacter::GetPlayerLootCount(int rarity)
{
	return m_player_loot_info.loot_count[(LootRarity)rarity];
}

void ACombatCharacter::AddPlayerLootCount(int rarity)
{
	FString str = "Loot Collected with Rarity: " + FString::FromInt(rarity) + " ]";
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);

	m_player_loot_info.loot_count[(LootRarity)rarity]++;
}


void ACombatCharacter::DecrementPlayerLootCount(int rarity)
{
	if (GetPlayerLootCount(rarity) > 0)
		m_player_loot_info.loot_count[(LootRarity)rarity]--;

}


bool ACombatCharacter::HasKey()
{
	return m_current_keys > 0;
}

void ACombatCharacter::UseKey()
{
	m_current_keys--;
	if (m_current_keys < 0)
		m_current_keys = 0;
}

void ACombatCharacter::AddKey(int amt)
{
	m_current_keys += amt;
}

void ACombatCharacter::decreasePlayerHealth(float damage_amount)
{
	if (this->player_current_health > 0.0f)
	{
		this->player_current_health -= (damage_amount * GetDifficultyModifier());
		if (this->player_current_health <= 0.0f)
		{
			OnPlayerDeath();
			should_update_score = true;
		}
			

		ClampPlayerHealth();
	}
}

void ACombatCharacter::increasePlayerHealth(float health_gained)
{
	if (this->player_current_health < this->player_max_health)
	{
		this->player_current_health += health_gained;
		ClampPlayerHealth();
	}
}

float ACombatCharacter::GetPlayerCurrentHealth()
{
	return this->player_current_health;
}

float ACombatCharacter::GetPlayerMaxHealth()
{
	return this->player_max_health;
}

float ACombatCharacter::GetPlayerHealthPercentage()
{
	if (this->player_max_health > 0.0f)
		return this->player_current_health / this->player_max_health;

	return 0.0f;
}

float ACombatCharacter::GetPlayerLerpingHealthPercentage()
{
	if (this->player_max_health > 0.0f)
		return this->player_lerping_health / this->player_max_health;

	return 0.0f;
}

void ACombatCharacter::ClampPlayerHealth()
{
	if (player_current_health > player_max_health)
		player_current_health = player_max_health;
	else if (player_current_health < 0)
	{
		player_current_health = 0;
	}
}

void ACombatCharacter::Tick(float delta_time)
{
	if (this->player_lerping_health > this->player_current_health)
	{
		this->player_lerping_health -= delta_time * 5.0f;
		if (this->player_lerping_health < this->player_lerping_health)
			this->player_lerping_health = this->player_current_health;
	}

	if (this->should_update_score)
	{
		timer += delta_time;
		if (timer > 0.15f)
		{
			timer = 0.0f;
			UpdateTotalScore();
		}
	}

	//Test for linking loot with UI
	/*static float testtimer = 0.0f;
	testtimer += delta_time;
	if (testtimer > 2.0f)
	{
		testtimer = 0.0f;
		AddPlayerLootCount(UKismetMathLibrary::RandomIntegerInRange(LR_COMMON, LR_LEGENDARY));
	}*/

	Super::Tick(delta_time);
}

void ACombatCharacter::ChangeDifficulty(int num)
{
	player_difficulty += num;

	const int max = 10;
	const int min = 1;

	if (player_difficulty < min) player_difficulty = min;
	if (player_difficulty > max) player_difficulty = max;
	
}

int ACombatCharacter::GetDifficulty()
{
	return this->player_difficulty;
}

float ACombatCharacter::GetDifficultyModifier()
{
	return 0.9f + (this->player_difficulty/ 10.f);
}

void ACombatCharacter::UpdateTotalScore()
{
	if (m_player_loot_info.loot_count[LR_COMMON] > 0)
	{
		m_total_score += 1;
		m_player_loot_info.loot_count[LR_COMMON]--;
	}
	else if (m_player_loot_info.loot_count[LR_UNCOMMON] > 0)
	{
		m_total_score += 3;
		m_player_loot_info.loot_count[LR_UNCOMMON]--;
	}
	else if (m_player_loot_info.loot_count[LR_RARE] > 0)
	{
		m_total_score += 7;
		m_player_loot_info.loot_count[LR_RARE]--;
	}
	else if (m_player_loot_info.loot_count[LR_EPIC] > 0)
	{
		m_total_score += 15;
		m_player_loot_info.loot_count[LR_EPIC]--;
	}

	else if (m_player_loot_info.loot_count[LR_LEGENDARY] > 0)
	{
		m_total_score += 25;
		m_player_loot_info.loot_count[LR_LEGENDARY]--;
	}
}

int ACombatCharacter::GetTotalScore()
{
	return this->m_total_score;
}

