// Fill out your copyright notice in the Description page of Project Settings.


#include "DifficultyInteractionObject.h"
#include "CombatCharacter.h"

ADifficultyInteractionObject::ADifficultyInteractionObject()
	: AManualLootObject()
{
	this->Increases_Difficulty = true;
}

void ADifficultyInteractionObject::Tick(float DeltaTime)
{
	//Nothing happens on tick
	AManualLootObject::Tick(DeltaTime);
}

void ADifficultyInteractionObject::Interact(ABaseController* controller)
{
	ACombatCharacter* p_char = (controller && controller->GetCharacter() ? Cast<ACombatCharacter>(controller->GetCharacter()) : NULL);
	if (p_char)
	{
		//Difficulty will be increased here, stored in managers somewhere later.
		if (this->Increases_Difficulty)
		{
			//Higher manager diff
			p_char->ChangeDifficulty(1);
		}
		else
		{
			//Lower manager diff
			p_char->ChangeDifficulty(-1);
		}

	}
	

	AManualLootObject::Interact(controller);
}