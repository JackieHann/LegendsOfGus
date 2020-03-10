// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.generated.h"

UCLASS()
class MYPROJECT2_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
private:
	UPROPERTY()
	AActor* player;
	UFUNCTION()
	void Idle();
	UFUNCTION()
	void GoToPlayer();
	UFUNCTION()
	void AttackPlayer();
	
};
