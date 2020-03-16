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

	if (DistanceToPlayer > AISightRadius)
	{
		bIsPlayerDetected = false;
	}

	if ((enemy->NextWaypoint != nullptr) && (bIsPlayerDetected == false))
	{
		MoveToActor(enemy->NextWaypoint, 1.0f);
	}
	else if (bIsPlayerDetected == true)
	{
		MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1.0f);
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
			bIsPlayerDetected = true;
		}
	}
}