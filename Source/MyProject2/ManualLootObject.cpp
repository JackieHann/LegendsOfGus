// Fill out your copyright notice in the Description page of Project Settings.


#include "ManualLootObject.h"
//#include "Engine.h"

void AManualLootObject::Interact(ABaseController* controller)
{
	AInteractableObject::Interact(controller);

	//Base interaction just makes the object disappear
	//Any inherited objects can have custom

	//FString str = "Interacted With Item [ " + this->GetName() + " ]";
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);

	if(this->Delete_On_Interact)
		Destroy();
}

void AManualLootObject::Tick(float DeltaTime)
{
	AInteractableObject::Tick(DeltaTime);

}