// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include <string>
#include "RoomActor.h"
#include "Map.h"

/**
 * 
 */

class MYPROJECT2_API LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void LM_DoSomething();

	void CreateLevel(const int seed);

	void SpawnRoomActor(std::string file_path, FVector world_pos, FRotator world_rot, int room_size, UObject* obj);
	
	UObject* GetObjectFromFile(FString file_path, FString object_name);

	void _CreateRoomsFromMap(Map map);

private:
	//Functions used by the CreateLevel Function Only
	void _CreateLevel(const int seed);
	void _CreateRoom(Room& room);

	Map m_curr_map;

};


