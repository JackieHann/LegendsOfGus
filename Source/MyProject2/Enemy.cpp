// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Constructors
AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer) :
	move_speed(1.0f),
	damage_modifier(1.0f),
	health(1.0f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// add capsule collider to root and resize
	// NEEDS MOVING TO POST CONSTRUCTOR INITIALIZE FUNCTION
	Collider = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule Collider"));
	Collider->InitCapsuleSize(100.0f, 100.0f);
	// Add overlap event to collider
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEnd);
	Collider->AttachTo(RootComponent);

	// Set enemy controller	
	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when something enters this actors collider
void AEnemy::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check which object has entered the collider
	if (otherActor && (otherActor != this) && otherComponent && otherActor->ActorHasTag("Player"))
	{
		FString text = ("Found player!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
	}
}

// Called when something leaves this actors collider
void AEnemy::OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex)
{
	// Check which object has left the collider
	if (otherActor && (otherActor != this) && otherComponent && otherActor->ActorHasTag("Player"))
	{
		FString text = ("Player gone!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
	}
}