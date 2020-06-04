
#include "DoorInteractionObject.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "CombatCharacter.h"

ADoorInteractionObject::ADoorInteractionObject()
{
	SFX_OpenDoor = NULL;
	SFX_LockedDoor = NULL;
	SFX_UnlockedDoor = NULL;

	AC_OpenDoor = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_OpenDoor"));
	AC_OpenDoor->SetupAttachment(RootComponent);

	AC_LockedDoor = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_LockedDoor"));
	AC_LockedDoor->SetupAttachment(RootComponent);

	AC_UnlockedDoor = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_UnlockedDoor"));
	AC_UnlockedDoor->SetupAttachment(RootComponent);


	//Key_Mesh = Utility
	//Key_Mesh =   CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key_Mesh"));
	//Key_Mesh->SetupAttachment(RootComponent);

	this->Opening = false;
	this->Closing = false;

	this->Locked = this->Door_Is_Locked;

	this->Door_Speed = 2.0f;
}

void ADoorInteractionObject::BeginPlay()
{
	Super::BeginPlay();
	if (SFX_OpenDoor) AC_OpenDoor->SetSound((USoundBase*)SFX_OpenDoor);
	if (SFX_LockedDoor) AC_LockedDoor->SetSound((USoundBase*)SFX_LockedDoor);
	if (SFX_UnlockedDoor) AC_UnlockedDoor->SetSound((USoundBase*)SFX_UnlockedDoor);

	TArray<UStaticMeshComponent*> my_components;
	this->GetComponents(my_components);
	for (auto StaticMeshComponent : my_components)
	{
		Key_Mesh = StaticMeshComponent;
	}

	if (Key_Mesh) 
		Key_Mesh->SetHiddenInGame(true);

	this->Opening = false;
	this->Closing = false;

	this->Locked = this->Door_Is_Locked;

	this->OriginalRotation = this->GetActorRotation().Yaw;

}




void ADoorInteractionObject::Interact(ABaseController* controller)
{
	AManualLootObject::Interact(controller);

	//Base interaction just makes the object disappear
	//Any inherited objects can have custom

	if (this->Locked)
	{
		//Check for key

		ACharacter* p_char = controller->GetCharacter();
		ACombatCharacter* character = p_char ? Cast<ACombatCharacter>(p_char) : NULL;
		if(character && character->HasKey())
		{
			character->UseKey();
			if (Key_Mesh) 
				Key_Mesh->SetHiddenInGame(false);

			this->Locked = false;
			//Play unlocked sfx
			//Play creaking door sfx
			if (AC_UnlockedDoor && SFX_UnlockedDoor)
			AC_UnlockedDoor->Play(0.f);
			
			return;

		}
		else
		{
			//Play locked sfx
			//Play creaking door sfx
			if (AC_LockedDoor && SFX_LockedDoor)
				AC_LockedDoor->Play(0.f);
			return;
		}

	}

	if (Opening == false)
	{

		//FVector heading = controller->GetPlayerWorldPos() - this->GetActorLocation();
		//float dot = GetHorizontalDotProductTo(GetWorld()->GetFirstPlayerController()->GetPawn());
		//AddRotation = dot > 0.0f ? 90.0f : -90.0f;

		Rotation = OriginalRotation + Door_Open_Angle;
		Opening = true;
		Closing = false;

		//Play creaking door sfx
		if(AC_OpenDoor && SFX_OpenDoor)
			AC_OpenDoor->Play(0.6f);
		
	}
	else if (Closing == false)
	{
		Rotation = OriginalRotation;
		Closing = true;
		Opening = false;

		//Play creaking door sfx;
		//Play creaking door sfx
		if (AC_OpenDoor && SFX_OpenDoor)
			AC_OpenDoor->Play(0.6f);
	}

	if (this->Delete_On_Interact)
		Destroy();
}

void ADoorInteractionObject::Tick(float DeltaTime)
{
	AManualLootObject::Tick(DeltaTime);

	//Make sure we don't update rotation of all doors unless we have interacted.
	if (Opening || Closing)
	{
		FRotator NewRotation = FMath::RInterpTo(this->GetActorRotation(), FRotator(0.0f, Rotation, 0.0f), DeltaTime, Door_Speed);
		this->SetActorRotation(NewRotation);
	}
}

FString ADoorInteractionObject::GetInteractText()
{
	FString action_section = (this->Locked ? FString::Printf(TEXT("Locked")) : this->Opening ? FString::Printf(TEXT("Close")) : FString::Printf(TEXT("Open")));
	return action_section;
}

FVector ADoorInteractionObject::GetWorldPos()
{
	if(Key_Mesh)
		return Key_Mesh->GetComponentTransform().GetLocation();

	return Super::GetWorldPos();
}