// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoLootObject.h"
#include "Engine.h"

// Sets default values
AAutoLootObject::AAutoLootObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAutoLootObject::Collect(ABaseController* controller)
{
	if(controller)
		this->OnCollect(controller);
}
void AAutoLootObject::OnCollect(ABaseController* controller)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Auto-Loot Object Found Within Range"));

}

// Called when the game starts or when spawned
void AAutoLootObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAutoLootObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

