// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include <string>
/**
 * 
 */
class MYPROJECT2_API LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void LM_DoSomething();

	void SpawnBlueprintActor(const char* file_path, FVector world_pos, FRotator world_rot);
};
