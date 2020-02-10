// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::SM_DoSomething()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Just Called A SceneManager Function!")));
}
