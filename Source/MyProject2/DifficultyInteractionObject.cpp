// Fill out your copyright notice in the Description page of Project Settings.


#include "DifficultyInteractionObject.h"

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
	//Difficulty will be increased here, stored in managers somewhere later.
	if (this->Increases_Difficulty)
	{
		//Higher manager diff
	}
	else
	{
		//Lower manager diff
	}

	AManualLootObject::Interact(controller);
}