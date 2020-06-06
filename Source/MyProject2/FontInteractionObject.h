// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableInteractionObject.h"
#include "FontInteractionObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AFontInteractionObject : public AConsumableInteractionObject
{
	GENERATED_BODY()
		
	AFontInteractionObject();
public:

	
	virtual void BeginPlay();

	virtual void Interact(ABaseController* controller) override;

	virtual FString GetInteractText() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root_Scene_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Overall_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Water_Plane_Mesh;
};
