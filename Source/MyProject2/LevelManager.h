// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include <string>
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

	void SpawnBlueprintActor(std::string file_path, FVector world_pos, FRotator world_rot);
	
	void _CreateRoomsFromMap(Map map);

private:
	//Functions used by the CreateLevel Function Only
	void _CreateLevel(const int seed);
	void _CreateRoom(Room& room);

	Map m_curr_map;

};


