// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManualLootObject.h"
#include "BaseController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "DoorInteractionObject.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT2_API ADoorInteractionObject : public AManualLootObject
{
	GENERATED_BODY()

public:

	virtual void BeginPlay();

	virtual void Interact(ABaseController* controller) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door_Settings, meta = (AllowPrivateAccess = "true"))
	float Door_Open_Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door_Settings, meta = (AllowPrivateAccess = "true"))
	bool Door_Is_Locked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door_Settings, meta = (AllowPrivateAccess = "true"))
	float Door_Speed;

	//Group sound variables into Audio classification
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* SFX_OpenDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* SFX_LockedDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* SFX_UnlockedDoor;

	class UStaticMeshComponent* Key_Mesh;

	virtual FString GetInteractText() override;

	virtual FVector GetWorldPos() override;

private:
	ADoorInteractionObject();

	bool Locked;
	bool Opening;
	bool Closing;

	float OriginalRotation;
	float Rotation;
	
	UAudioComponent* AC_LockedDoor;
	UAudioComponent* AC_OpenDoor;
	UAudioComponent* AC_UnlockedDoor;
};
