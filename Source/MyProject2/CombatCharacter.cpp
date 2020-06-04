// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"
#include "Enemy.h"
#include "Engine.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Called Combat Actor Constructor.."));
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


