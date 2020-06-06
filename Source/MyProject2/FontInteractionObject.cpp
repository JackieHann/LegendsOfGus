// Fill out your copyright notice in the Description page of Project Settings.


#include "FontInteractionObject.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"

AFontInteractionObject::AFontInteractionObject()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));

	this->Overall_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Overall Mesh"));
	this->Water_Plane_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water Mesh"));
	this->Overall_Mesh->AttachTo(RootComponent);
	this->Water_Plane_Mesh->AttachTo(RootComponent);

}

void AFontInteractionObject::BeginPlay()
{
	Super::BeginPlay();

	if (this->Overall_Mesh) Overall_Mesh->SetHiddenInGame(false);
	if (this->Water_Plane_Mesh) Water_Plane_Mesh->SetHiddenInGame(false);

	//this->Water_Plane_Mesh->SetLocal
	//this->Water_Plane_Mesh->SetWorldLocation(this->Overall_Mesh->position)

}

void AFontInteractionObject::Interact(ABaseController* controller)
{
	AConsumableInteractionObject::Interact(controller);

	if (this->current_charges == 0)
	{
		if (this->Water_Plane_Mesh) Water_Plane_Mesh->SetHiddenInGame(true);
	}
}

void AFontInteractionObject::Tick(float DeltaTime)
{
	AConsumableInteractionObject::Tick(DeltaTime);
}

FString AFontInteractionObject::GetInteractText()
{
	FString action_section = (this->current_charges > 0 ? FString::Printf(TEXT("Drink")) : FString::Printf(TEXT("Empty")));
	return action_section;
}