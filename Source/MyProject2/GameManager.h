// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/UObjectBase.h"
#include "LevelManager.h"
#include "SceneManager.h"
#include "Engine.h"
#include "GameManager.generated.h"

/**
 * A Singleton Class that is used to store multiple managers within its contents
 * IE: A 'General Manager' class
 */

UCLASS(blueprintable, BlueprintType, ClassGroup = (custom), meta = (BlueprintSpawnableObject))
class MYPROJECT2_API UGameManager : public UObject
{
	GENERATED_BODY()
protected:


public:
	UGameManager(const FObjectInitializer& ObjectInitializer);


	//Store all 'manager' objects within one general manager class
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Manager")
	LevelManager _levelManager;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Manager")
	SceneManager _sceneManager;

	int _managerID;
};


//'Global' Getters that return a pointer to their respective managers
UGameManager* GetGameManager();
LevelManager* GetLevelManager();
SceneManager* GetSceneManager();