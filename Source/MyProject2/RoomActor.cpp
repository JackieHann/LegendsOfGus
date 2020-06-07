// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomActor.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "GameManager.h"

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
	EnterTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoomActor::OnOverlapBegin);

}

ARoomActor::ARoomActor(FString filepath)
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
	EnterTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoomActor::OnOverlapBegin);

}


// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Get list of all components of this room
	TInlineComponentArray<UChildActorComponent*> components;
	GetComponents(components);

	// add waypoints to waypoint list
	for (auto& component : components)
	{
		// For all waypoint components
		if (component->GetChildActorTemplate()->IsA(AEnemyWaypoint::StaticClass()))
		{
			AEnemyWaypoint* waypoint = Cast<AEnemyWaypoint>(component->GetChildActor());
			// Add waypoints to list of possible waypoints - dont add THIS waypoint
			//if (*waypoint != this)
			waypoints.Add(waypoint);
		}
	}

	for (auto& waypoint : waypoints)
	{
		// Setup possible next waypoints for each waypoint
		waypoint->addPossibleWaypoints(waypoints);
	}
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called on collider overlap
void ARoomActor::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 
	// Need to check if the object doing the colliding is the player
	if (!bRoomEntered && otherActor && (otherActor != this) && otherComponent && otherActor->ActorHasTag("Player"))
	{
		// Tags for each type of spawner
		FName tag_melee = "Spawner.Melee";
		FName tag_ranged = "Spawner.Ranged";

		// Get room object
		AActor* parent = overlappedComponent->GetOwner();
		// Create list of all child actor components
		TInlineComponentArray<UChildActorComponent*> components;
		parent->GetComponents(components);

		for (auto& component : components)
		{
			// Ignore any components that are not spawners
			if (component->GetChildActorTemplate()->IsA(AEnemySpawner::StaticClass()))
			{
				AEnemySpawner* spawner = Cast<AEnemySpawner>(component->GetChildActor());
				FString text;
				// If component is a melee enemy spawner
				if (spawner->ActorHasTag(tag_melee))
				{
					// Get position of spawner
					FVector spawn_pos = spawner->GetActorLocation();

					// Add height so enemy doesnt spawn in the ground
					spawn_pos.Z = spawn_pos.Z + 200.0f;
					// Get spawner rotation so enemy faces correct direction - cant tell with cube!
					FRotator spawn_rot = spawner->GetActorRotation();
					// Spawn an enemy at the spawners locationS
					//const char* melee_enemy_file_path = "Blueprint'/Game/Blueprints/Enemies/Enemy_BP.Enemy_BP'";
					//UObject* blueprint = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, ANSI_TO_TCHAR(melee_enemy_file_path)));
					
					UObject* enemy_obj = GetLevelManager()->GetObjectFromFile("/Game/Blueprints/Enemies", "Enemy_BP");
					if (enemy_obj)
					{
						UClass* enemy_class = Cast<UClass>(enemy_obj);
						if (enemy_class == NULL)
							return;

						ACharacter* spawned_character = GetWorld()->SpawnActor<ACharacter>(enemy_class, spawn_pos, spawn_rot);
						AEnemy* spawned_enemy = Cast<AEnemy>(spawned_character);
						spawned_enemy->SpawnRoom = this;
					}
				}
			}
		}	
		bRoomEntered = true;
	}
}

AEnemyWaypoint* ARoomActor::getRandomStartWaypoint() 
{
	int32 index = FMath::RandRange(0, waypoints.Num() - 1);
	return waypoints[index];
}

