// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

class ABaseController;

UCLASS()
class MYPROJECT2_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FString identity;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//What happens on interaction?
	virtual void Interact(ABaseController* controller);

	//Capitalized For Visual In Editor..
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Action;

	UPROPERTY(EditDefaultsOnly)
	FString Key;

	UPROPERTY(EditDefaultsOnly)
	bool Enable_Widget;

	UPROPERTY(EditDefaultsOnly)
	FVector Widget_Offset;

	UPROPERTY(EditDefaultsOnly)
	bool Delete_On_Interact;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool GetWidgetEnabled();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FVector GetWorldPos();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FVector GetOffset();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetInteractText();

};
