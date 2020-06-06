// Fill out your copyright notice in the Description page of Project Settings.


#include "GearLootObject.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "CombatCharacter.h"

AGearLootObject::AGearLootObject()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));

	this->Sphere_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	this->Sphere_Mesh->AttachTo(RootComponent);

	this->Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	this->Collider->AttachTo(this->Sphere_Mesh);

	//Not a great way of doing this, should ideally pass through the material/name etc later on.
	Legendary_Material = NULL;
	Epic_Material = NULL;
	Rare_Material = NULL;
	Uncommon_Material = NULL;
	Common_Material = NULL;

	this->Sphere_Mesh->SetSimulatePhysics(true);
}

void AGearLootObject::BeginPlay()
{

	RandomizeRarity();
	RandomizeName();

	UpdateMaterial();

	FString str = "Loot Spawned with Name: " + loot_name + " and Rarity: " + FString::FromInt(loot_rarity) + " ]";
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);

}

void AGearLootObject::DeleteSelf()
{
	Sphere_Mesh->DestroyComponent();
	Collider->DestroyComponent();

	Destroy();
}

FString AGearLootObject::GetInteractText()
{
	FString action_section = loot_name;

	return action_section;
}

void AGearLootObject::Interact(ABaseController* controller)
{
	if (controller)
	{
		ACombatCharacter* ch = Cast<ACombatCharacter>(controller->GetCharacter());
		if (ch)
		{

			ch->AddPlayerLootCount(loot_rarity);
		}
	}

	AManualLootObject::Interact(controller);
};

void AGearLootObject::RandomizeRarity()
{
	int randomized = UKismetMathLibrary::RandomIntegerInRange(0, 100);
	int new_loot_rarity = 0;

	if (randomized < common_threshold)
		new_loot_rarity = 0;
	else if (randomized < uncommon_threshold)
		new_loot_rarity = 1;
	else if (randomized < rare_threshold)
		new_loot_rarity = 2;
	else if (randomized < epic_threshold)
		new_loot_rarity = 3;
	else
		new_loot_rarity = 4;


	loot_rarity = new_loot_rarity;
}

void AGearLootObject::RandomizeName()
{
	FString new_name = "";
	if (PotentialStrings.Num() > 0)
		new_name = PotentialStrings[UKismetMathLibrary::RandomIntegerInRange(0, PotentialStrings.Num() - 1)];

	loot_name = new_name;
}

void AGearLootObject::UpdateMaterial()
{
	if (Sphere_Mesh)
	{
		switch (loot_rarity)
		{
		case 0:
			Sphere_Mesh->SetMaterial(0, Common_Material);
			break;
		case 1:
			Sphere_Mesh->SetMaterial(0, Uncommon_Material);
			break;
		case 2:
			Sphere_Mesh->SetMaterial(0, Rare_Material);
			break;
		case 3:
			Sphere_Mesh->SetMaterial(0, Epic_Material);
			break;
		case 4:
			Sphere_Mesh->SetMaterial(0, Legendary_Material);
			break;
		}
	}
}

FSlateColor AGearLootObject::GetInteractColour()
{
	FSlateColor new_color = Common_Text_Colour;
	switch (loot_rarity)
	{
	case 0:
		new_color = Common_Text_Colour;
		break;
	case 1:
		new_color = Uncommon_Text_Colour;
		break;
	case 2:
		new_color = Rare_Text_Colour;
		break;
	case 3:
		new_color = Epic_Text_Colour;
		break;
	case 4:
		new_color = Legendary_Text_Colour;
		break;
	}

	return new_color;
}

FVector AGearLootObject::GetWorldPos()
{
	if (Sphere_Mesh)
		return Sphere_Mesh->GetComponentTransform().GetLocation();

	return Super::GetWorldPos();
}