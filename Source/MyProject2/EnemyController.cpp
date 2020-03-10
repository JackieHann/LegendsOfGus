// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

void AEnemyController::BeginPlay()
{
	// Get player actor
	player = UGameplayStatics::GetPlayerPawn(this, 0);
	FString text = ("New enemy controller - " + player->GetName());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
	GoToPlayer();
}

void AEnemyController::Idle()
{
	FString text = ("Enemy idling...");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}

void AEnemyController::GoToPlayer()
{
	FString text = ("Enemy following player...");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
	MoveToActor(player);
}

void AEnemyController::AttackPlayer()
{
	FString text = ("Enemy attacking player...");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}