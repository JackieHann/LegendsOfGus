// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPortalInteractionObject.h"
#include "CombatCharacter.h"

void AEndPortalInteractionObject::Interact(ABaseController* controller)
{
	ACombatCharacter* p_char = Cast<ACombatCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (p_char)
	{
		p_char->SetWon();
	}

	APortalInteractionObject::Interact(controller);
}