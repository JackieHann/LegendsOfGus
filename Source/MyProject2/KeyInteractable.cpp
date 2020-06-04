// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyInteractable.h"
#include "CombatCharacter.h"
void AKeyInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AKeyInteractable::Interact(ABaseController* controller)
{
	ACharacter* p_char = controller->GetCharacter();
	ACombatCharacter* character = p_char ? Cast<ACombatCharacter>(p_char) : NULL;
	if (character)
	{
		character->AddKey(1);
	}
	AManualLootObject::Interact(controller);
}