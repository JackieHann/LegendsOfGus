// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalInteractionObject.h"
#include "BaseController.h"
#include "Engine/World.h"

APortalInteractionObject::APortalInteractionObject()
	: AManualLootObject()
{
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

		//Also, reset stats etc here..
	}

	AManualLootObject::Interact(controller);
}