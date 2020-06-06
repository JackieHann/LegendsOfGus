// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Styling/SlateColor.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	bool Enable_Name_Tooltip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	FString Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	bool Enable_Action_Tooltip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	FString Key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	bool Enable_Key_Tooltip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Enable_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Widget_Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Delete_On_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	FSlateColor Interact_Colour;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool GetWidgetEnabled();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual FVector GetWorldPos();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FVector GetOffset();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual FString GetInteractText();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual FSlateColor GetInteractColour();

};
