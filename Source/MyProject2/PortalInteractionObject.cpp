// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalInteractionObject.h"
#include "BaseController.h"
#include "CombatCharacter.h"
#include "Engine/World.h"

APortalInteractionObject::APortalInteractionObject()
	: AManualLootObject()
{
	Is_Start_Dungeon_Spawn = true;
	this->Target_World_Position.Set(0, 0, 0);
}

void APortalInteractionObject::Tick(float DeltaTime)
{
	//Nothing happens on tick
	AManualLootObject::Tick(DeltaTime);
}

void APortalInteractionObject::Interact(ABaseController* controller)
{
	//If we have a valid player controller, and our rooms are all loaded
	bool rooms_spawned = true;
	if (controller &&
		controller->GetPawn() &&
		rooms_spawned)
	{
		//Valid teleport, so tele
		controller->GetPawn()->SetActorLocation(Target_World_Position);
		//FRotator origin_rotation = { 0, 180, 0 };
		//controller->GetPawn()->SetActorRotation(origin_rotation);
		//Also, reset stats etc here..
	}

	AManualLootObject::Interact(controller);
}

FString APortalInteractionObject::GetInteractText()
{
	ACombatCharacter* p_char = Cast<ACombatCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (p_char && this->Is_Start_Dungeon_Spawn)
	{
		FString action_section = (FString::Printf(TEXT("Enter Dungeon (+%i)"), p_char->GetDifficulty()));
		return action_section;
	}

	return AManualLootObject::GetInteractText();
}