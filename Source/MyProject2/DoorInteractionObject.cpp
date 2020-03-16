
#include "DoorInteractionObject.h"

ADoorInteractionObject::ADoorInteractionObject()
{
	this->originalRotation = GetActorRotation().Yaw;
	this->Opening = false;
	this->Closing = false;
}

void ADoorInteractionObject::Interact(ABaseController* controller)
{
	AInteractableObject::Interact(controller);

	//Base interaction just makes the object disappear
	//Any inherited objects can have custom

	//FString str = "Interacted With Item [ " + this->GetName() + " ]";
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);

	if (Opening == false)
	{
		Opening = true;
		Closing = false;
	}
	else if (Closing == false)
	{
		Closing = true;
		Opening = false;
	}

	if (this->Delete_On_Interact)
		Destroy();
}

void ADoorInteractionObject::Tick(float DeltaTime)
{
	AManualLootObject::Tick(DeltaTime);

	if (Opening)
	{
		DoorCurrentRotation = this->GetActorRotation().Yaw;

		AddRotation = DeltaTime * 80;
		FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		this->SetActorRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
	
	if(Closing)
	{
		DoorCurrentRotation = this->GetActorRotation().Yaw;
		AddRotation = DeltaTime * -80;
		FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		this->SetActorRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}


}