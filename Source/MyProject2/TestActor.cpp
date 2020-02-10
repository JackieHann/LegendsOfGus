// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

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

	GetLevelManager()->CreateLevel(1);
	//When weve got room data, spawn it somewhere
	//SpawnRoom(room_data, grid_pos)

	/*const float unreal_individual_tile_size = 100.f;
	const float our_scale = 4.0f;
	float room_size = 3.0f;
	float offset = (room_size / 2.f) * (unreal_individual_tile_size * our_scale);

	const float cell_to_unreal_size = (unreal_individual_tile_size * our_scale);

	//Stuff that would be in room_data
	int x1 = 0;
	int y1 = 0;
	int roomsize1 = 3;

	//Take that out, scale it to unreal
	float x1Scaled = x1 * cell_to_unreal_size;
	float y1Scaled = y1 * cell_to_unreal_size;
	float offset1 = ((float)roomsize1 / 2.f) * cell_to_unreal_size;

	GetLevelManager()->SpawnBlueprintActor("Rooms/3x3_2door_straight_BP.3x3_2door_straight_BP'", { x1Scaled + offset1, y1Scaled + offset1, 0 }, FRotator(0, 0, 0));

	//same for next room
	int x2 = 3;
	int y2 = 0;
	int roomsize2 = 3;

	float x2Scaled = x2 * cell_to_unreal_size;
	float y2Scaled = y2 * cell_to_unreal_size;
	float offset2 = ((float)roomsize2 / 2.f) * cell_to_unreal_size;
	GetLevelManager()->SpawnBlueprintActor("Rooms/3x3_2door_straight_BP.3x3_2door_straight_BP'", { x2Scaled + offset2, y2Scaled + offset2, 0 }, FRotator(0, 0, 0));*/
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

