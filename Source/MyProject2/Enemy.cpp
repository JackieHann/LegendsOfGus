// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
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
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);

	// Set enemy controller	
	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	// Set death sound for enemy
	hitSound = CreateDefaultSubobject<UAudioComponent>(FName("Enemy Damaged Sound"));
	static ConstructorHelpers::FObjectFinder<USoundCue> enemyHitSound(TEXT("/Game/Sound/Enemies/Damaged/EnemyHit.EnemyHit"));
	hitSound->Sound = enemyHitSound.Object;
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

	//Aka timeout
	if (this->should_timeout)
	{
		time_before_removal -= DeltaTime;
		if (time_before_removal < 0.f)
		{
			this->Destroy();
		}
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

		}
	}
}

// Called when the enemy takes damage from the player
void AEnemy::decreaseEnemyHealth(float damage_amount)
{
	hitSound->Play();
	EnemyHealth -= damage_amount;
	if (EnemyHealth <= 0.0f)
	{
		should_timeout = true;
		EnemyHealth = 0.0f;
		SetActorEnableCollision(false);
	}
		
}

void AEnemy::setRandomIdleTime()
{
	idle_time_current = FMath::RandRange(idle_time_min, idle_time_max);
}