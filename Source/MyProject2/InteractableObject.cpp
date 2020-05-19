// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "BaseController.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	identity = GetName();

	Name = "*name*";
	Enable_Name_Tooltip = true;

	Key = "F";
	Enable_Key_Tooltip = true;

	Action = "*action*";
	Enable_Action_Tooltip = true;

	Widget_Offset = { 0, 0, 0 };
	Enable_Widget = true;
	Delete_On_Interact = true;

}

void AInteractableObject::Interact(ABaseController* controller)
{
	//Skeleton to override
	FString str = "Interacted With Item [ " + this->GetName() + " ]";
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);
}

bool AInteractableObject::GetWidgetEnabled()
{
	return this->Enable_Widget;
}

FVector AInteractableObject::GetWorldPos()
{
	return GetActorLocation();
}

FVector AInteractableObject::GetOffset()
{
	return this->Widget_Offset;
}

FString AInteractableObject::GetInteractText()
{

	FString name_section	= (this->Enable_Name_Tooltip	? FString::Printf(TEXT("%s : "), *Name) : "");
	FString key_section		= (this->Enable_Key_Tooltip		? FString::Printf(TEXT("Press %s to "), *Key) : "");
	FString action_section	= (this->Enable_Action_Tooltip	? FString::Printf(TEXT("%s"), *Action) : "");

	//if (this->Enable_Action_Tooltip && this->Enable_Name_Tooltip && this->Enable_Key_Tooltip)
	return name_section + key_section + action_section;
	//   FString::Printf(TEXT("%s : Press %s to %s"), *Name, *Key, *Action);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

