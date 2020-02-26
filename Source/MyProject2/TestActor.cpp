// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"
#include <ctime>

// Sets default values
ATestActor::ATestActor()
	: timer(0.f), spawned(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	GetLevelManager()->CreateLevel(time(0));
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;

	if (timer > 1.f && !spawned)
	{
		
		spawned = true;
	}
}

