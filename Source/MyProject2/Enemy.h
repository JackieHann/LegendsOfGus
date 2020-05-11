// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "RoomActor.h"
#include "Enemy.generated.h"

UCLASS()
class MYPROJECT2_API AEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this character's properties
	AEnemy(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AEnemyWaypoint* NextWaypoint;

	UPROPERTY(EditAnywhere)
	ARoomActor* SpawnRoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex);
};
