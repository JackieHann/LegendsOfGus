// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "EnemyWaypoint.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MovableCharacter.h"

// Constructor
AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent() != nullptr)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("All Systems Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy controller broke!"));
	}
}

void AEnemyController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);
}

void AEnemyController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AEnemy* enemy = Cast<AEnemy>(GetPawn());

	// if enemy is alive then move
	if (enemy->EnemyHealth != 0.0f)
	{ 
		// IF player goes out of sight range, stop chasing
		if (DistanceToPlayer > AISightRadius)
		{
			enemy->bIsPlayerDetected = false;
		}
		// if player isnt detected, path to waypoint
		if ((enemy->NextWaypoint != nullptr) && (enemy->bIsPlayerDetected == false))
		{
			enemy->bFollowingWaypoints = true;
			MoveToActor(enemy->NextWaypoint, 1.0f);
		}
		// If player is detected, move to player
		else if (enemy->bIsPlayerDetected == true)
		{
			DistanceToPlayer = GetPawn()->GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			enemy->bFollowingWaypoints = false;
			if (DistanceToPlayer < 200.0f)
			{
				enemy->bFollowingPlayer = false;
				enemy->bAttackingPlayer = true;
				MoveToActor(enemy, 1.0f);
			}
			else
			{
				enemy->bAttackingPlayer = false;
				enemy->bFollowingPlayer = true;
				MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f);
			}
		}
	}
	// if enemy is dead then stop moving completely
	else
	{
		enemy->bAttackingPlayer = false;
		enemy->bFollowingPlayer = false;
		enemy->bFollowingWaypoints = false;
		enemy->bIsPlayerDetected = false;
		MoveToActor(enemy, 1.0f);
	}

	
}

FRotator AEnemyController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AEnemyController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	for (int i = 0; i < DetectedPawns.Num(); i++)
	{
		if (!(DetectedPawns[i]->IsA(AEnemy::StaticClass())))
		{ 
			DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
			Cast<AEnemy>(GetPawn())->bIsPlayerDetected = true;
		}
	}
}