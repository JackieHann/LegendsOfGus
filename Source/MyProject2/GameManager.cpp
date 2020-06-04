// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

UGameManager::UGameManager(const FObjectInitializer& ObjectInitializer)
{
	_managerID = this->GetUniqueID();
}

UGameManager* GetGameManager()
{
	UGameManager* Instance = Cast < UGameManager >(GEngine->GameSingleton);
	if (!Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Get Game Manager"));
		return NULL;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Manager Called With ID: %i"), Instance->_managerID);
	}

	return Instance;
}

LevelManager* GetLevelManager()
{
	UGameManager* manager = GetGameManager();
	if (!manager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Get Level Manager"));
		return NULL; // also error
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Manager Called With ID: %i"), manager->_managerID);
	}

	return &(manager->_levelManager);
}

SceneManager* GetSceneManager()
{
	UGameManager* manager = GetGameManager();
	if (!manager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Get Scene Manager"));
		return NULL; // also error
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Scene Manager Called With ID: %i"), manager->_managerID);
	}
	return &(manager->_sceneManager);
}