// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"
#include "Enemy.h"
#include "Engine.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Called Combat Actor Constructor.."));

	player_current_health = player_max_health;
	m_current_keys = 0;
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
		this->player_current_health -= damage_amount;
		if (this->player_current_health <= 0.0f)
			OnPlayerDeath();

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


}



