// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::LM_DoSomething()
{
}

void LevelManager::SpawnBlueprintActor(const char* file_path, FVector world_pos, FRotator world_rot)
{
	char buffer[100];
	const char* root_dir = "Blueprint'/Game/Blueprints/";
	strcpy(buffer, root_dir);
	strcat(buffer, file_path);

	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, ANSI_TO_TCHAR(buffer)));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if (!SpawnActor)
	{
		return;
	}

	UClass* SpawnClass = SpawnActor->StaticClass();
	if (SpawnClass == NULL)
	{
		return;
	}

	UWorld* World = GWorld;
	World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, world_pos, world_rot);
}
