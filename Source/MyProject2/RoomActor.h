// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include <string>
#include "EnemySpawner.h"
#include "Enemy.h"
#include "RoomActor.generated.h"

UCLASS()
class MYPROJECT2_API ARoomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomActor();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* EnterTrigger;
	bool bRoomEntered;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Test() { int i = 0; }

	void InitializeRoom(float roomsize)
	{
		if (EnterTrigger)
		{
			EnterTrigger->SetBoxExtent({ roomsize * 200.f, roomsize * 200.f, 200.0f });
		}
	}

};
