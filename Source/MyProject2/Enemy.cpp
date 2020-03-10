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

	// add mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Enemy Mesh"));
	UStaticMesh* staticMesh = MeshAsset.Object;
	Mesh->SetStaticMesh(staticMesh);
	// set affected by gravity
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);
	// set mesh as root component
	RootComponent = Mesh;
	// add capsule collider to root and resize
	Collider = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule Collider"));
	Collider->InitCapsuleSize(100.0f, 100.0f);
	// Add overlap event to collider
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEnd);
	Collider->AttachTo(RootComponent);
	
	

	
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