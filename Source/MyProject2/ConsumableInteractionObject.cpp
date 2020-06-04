// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableInteractionObject.h"

AConsumableInteractionObject::AConsumableInteractionObject()
{
	this->Charges = 1;
	this->Health_Restored = 0;
	this->Destroy_On_Consume = true;
	this->Show_Charges_UI = false;
}

void AConsumableInteractionObject::BeginPlay()
{
	this->current_charges = this->Charges;
	Super::BeginPlay();
}

void AConsumableInteractionObject::Interact(ABaseController* controller)
{
	if (this->current_charges > 0)
	{
		Consume();
	}
	AManualLootObject::Interact(controller);
}

void AConsumableInteractionObject::Consume()
{
	this->current_charges--;
	if (this->current_charges < 0) this->current_charges = 0;

	//Handle Player Health Here
	//PlayerHealth += Health_Restored;
	FString str = "Player Consumed item and restored health.";
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, str);
}

FString AConsumableInteractionObject::GetInteractText()
{
	FString action_section = (this->Enable_Action_Tooltip ? FString::Printf(TEXT("%s (+%u)"), *Action, Health_Restored) : "");

	return action_section;
}

bool AConsumableInteractionObject::OverridesDeletion()
{
	return Destroy_On_Consume && this->Charges;
}