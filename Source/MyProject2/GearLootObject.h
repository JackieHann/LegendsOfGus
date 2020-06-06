// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManualLootObject.h"
#include "CombatCharacter.h"
#include "GearLootObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AGearLootObject : public AManualLootObject
{
	GENERATED_BODY()
public:
	virtual void BeginPlay();
	virtual void Interact(ABaseController* controller) override;

	virtual void DeleteSelf() override;
	virtual FVector GetWorldPos() override;

	virtual FString GetInteractText() override;
	virtual FSlateColor GetInteractColour() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Sphere_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> PotentialStrings;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Legendary, meta = (AllowPrivateAccess = "true"))
	float legendary_threshold = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Epic, meta = (AllowPrivateAccess = "true"))
	float epic_threshold = 85.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rare, meta = (AllowPrivateAccess = "true"))
	float rare_threshold = 75.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Uncommon, meta = (AllowPrivateAccess = "true"))
	float uncommon_threshold = 60.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Common, meta = (AllowPrivateAccess = "true"))
	float common_threshold = 30.f;

	UPROPERTY(EditAnywhere, Category = Legendary, meta = (AllowPrivateAccess = "true"))
	class UMaterial* Legendary_Material;

	UPROPERTY(EditAnywhere, Category = Epic, meta = (AllowPrivateAccess = "true"))
	class UMaterial* Epic_Material;

	UPROPERTY(EditAnywhere, Category = Rare, meta = (AllowPrivateAccess = "true"))
	class UMaterial* Rare_Material;

	UPROPERTY(EditAnywhere, Category = Uncommon, meta = (AllowPrivateAccess = "true"))
	class UMaterial* Uncommon_Material;

	UPROPERTY(EditAnywhere, Category = Common, meta = (AllowPrivateAccess = "true"))
	class UMaterial* Common_Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Legendary)
	FSlateColor Legendary_Text_Colour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Epic)
	FSlateColor Epic_Text_Colour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rare)
	FSlateColor Rare_Text_Colour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Uncommon)
	FSlateColor Uncommon_Text_Colour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Common)
	FSlateColor Common_Text_Colour;

private:

	
	FString loot_name;
	int loot_rarity;

	void RandomizeRarity();
	void RandomizeName();
	void UpdateMaterial();

	AGearLootObject();

};
