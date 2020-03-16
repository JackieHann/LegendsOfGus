// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EnemyWaypoint.generated.h"

UCLASS()
class MYPROJECT2_API AEnemyWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyWaypoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent*  Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AEnemyWaypoint*> PossibleWaypoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnEnemyEnter(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	AEnemyWaypoint* getRandomNextWaypoint();

	UFUNCTION()
	void addPossibleWaypoints(TArray<AEnemyWaypoint*> waypoints);
};
