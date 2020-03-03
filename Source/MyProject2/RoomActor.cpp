// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomActor.h"

// Sets default values
ARoomActor::ARoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bRoomEntered = false;

	// Add new root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Room"));
	// Create box collider component - for detecting if player is within room bounds
	EnterTrigger = CreateDefaultSubobject<UBoxComponent>(FName("Collider"));
	// Attach box collider to root component
	EnterTrigger->AttachTo(RootComponent);
	// Allow room trigger to generate overlap events
	EnterTrigger->SetGenerateOverlapEvents(true);
	// Add overlap event to collider
	EnterTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoomActor::onOverlapBegin);

}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called on collider overlap
void ARoomActor::onOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 
	// Need to check if the object doing the colliding is the player
	if (!bRoomEntered && otherActor && (otherActor != this) && otherComponent)
	{
		// Tags for each type of spawner
		FName tag_melee = "Spawner.Melee";
		FName tag_ranged = "Spawner.Ranged";

		// Get room object
		AActor* parent = overlappedComponent->GetOwner();
		// Create list of all child actor components
		TArray<UChildActorComponent*> components;
		parent->GetComponents(components);
		for (auto& component : components)
		{
			FString componentName = component->GetName();
			FString text;
			// If component is a melee enemy spawner
			if (component->GetChildActorTemplate()->ActorHasTag(tag_melee))
			{
				text = ("Found a spawner: " + componentName);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
			}
		}	
		bRoomEntered = true;
	}
}

