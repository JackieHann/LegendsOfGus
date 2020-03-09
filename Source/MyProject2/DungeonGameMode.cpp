// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameMode.h"
#include "UObject/ConstructorHelpers.h"

ADungeonGameMode::ADungeonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}