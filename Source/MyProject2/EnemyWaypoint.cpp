// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyWaypoint.h"
#include "Enemy.h"

// Sets default values
AEnemyWaypoint::AEnemyWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Waypoint Collider"));
	BoxCollider->SetupAttachment(GetRootComponent());
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyWaypoint::OnEnemyEnter);
}

// Called when the game starts or when spawned
void AEnemyWaypoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AEnemyWaypoint* AEnemyWaypoint::getRandomNextWaypoint()
{
	int32 index = FMath::RandRange(0, PossibleWaypoints.Num() - 1);
	return PossibleWaypoints[index];
}

void AEnemyWaypoint::OnEnemyEnter(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = nullptr;
	if (otherActor != nullptr)
	{
		enemy = Cast<AEnemy>(otherActor);
		if (enemy != nullptr && (enemy->bFollowingPlayer == false))
		{
			enemy->bFollowingWaypoints = false;
			enemy->bIsIdling = true;
			enemy->setRandomIdleTime();
		}
	}
}

void AEnemyWaypoint::addPossibleWaypoints(TArray<AEnemyWaypoint*> waypoints)
{
	for (int index = 0; index < waypoints.Num(); index++)
	{ 
		if (this->GetActorLocation() != waypoints[index]->GetActorLocation())
			PossibleWaypoints.Add(waypoints[index]);
	}
	
}
