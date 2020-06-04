// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyController.h"
#include "EnemyWaypoint.h"


// Constructors
AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// add capsule collider
	Collider = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule Collider"));
	Collider->AttachTo(RootComponent);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	// Set enemy controller	
	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();	
	if (Collider)
	{ 
		Collider->InitCapsuleSize(100.0f, 100.0f);
		Collider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
		Collider->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEnd);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Set next waypoint to be a random one in the room if there isnt one set
	if ((SpawnRoom != nullptr) && (SpawnRoom->waypoints.Num() != 0) && NextWaypoint == nullptr)
	{
		NextWaypoint = SpawnRoom->getRandomStartWaypoint();
	}
}


// Called when something enters this actors collider
void AEnemy::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check which object has entered the collider
	if (otherActor && (otherActor != this) && otherComponent)
	{
		if (otherActor->ActorHasTag("Waypoint"))
		{
			//FString text = ("Found waypoint: " + otherActor->GetName());
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
		}
	}
}


// Called when something leaves this actors collider
void AEnemy::OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex)
{
	// Check which object has left the collider
	if (otherActor && (otherActor != this) && otherComponent)
	{
		if (otherActor->ActorHasTag("Waypoint"))
		{
			//FString text = ("Left waypoint: " + otherActor->GetName());
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
		}
	}
}

// Called when the enemy takes damage from the player
void AEnemy::decreaseEnemyHealth(float damage_amount)
{
	EnemyHealth -= damage_amount;
	if (EnemyHealth <= 0.0f)
	{
		EnemyHealth = 0.0f;
		SetActorEnableCollision(false);
		//this->Collider->SetGenerateOverlapEvents(false);
	}
		
}