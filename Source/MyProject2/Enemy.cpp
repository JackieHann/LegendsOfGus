// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Constructors
AEnemy::AEnemy() :
	move_speed(1.0f),
	damage_modifier(1.0f),
	health(1.0f)
{
	// Get cube mesh -  will be changed to actual model, only need to do once as mesh doesnt change for different enemies
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// add root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Enemy"));
	// add capsule collider - needs to be resized on creation
	Collider = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule Collider"));
	// Attach capsule to root
	Collider->AttachTo(RootComponent);
	// Add mesh - will be changed to appropriate model
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Enemy Mesh"));
	Mesh->AttachTo(RootComponent);
	UStaticMesh* staticMesh = MeshAsset.Object;
	Mesh->SetStaticMesh(staticMesh);
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

