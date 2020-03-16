// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableCharacter.h"
#include "Engine.h"
#include "BaseController.h"

#include "InteractableObject.h"
#include "AutoLootObject.h"
#include "BasicLootObject.h"

// Sets default values
AInteractableCharacter::AInteractableCharacter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Called Interactable Actor Constructor.."));

	//Default Sphere Radius Setup
	m_loot_collider = CreateDefaultSubobject<USphereComponent>(TEXT("LootCollider"));
	m_loot_collider->SetupAttachment(RootComponent);
	m_loot_collider->SetSphereRadius(150.f); //150 seems reasonable?
}

void AInteractableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AInteractableCharacter::Interact);

}

void AInteractableCharacter::Interact()
{
	ABaseController* IController = Cast<ABaseController>(GetController());
	if (IController && IController->HasTargetInteractable())
	{
		ABasicLootObject* interactable = Cast<ABasicLootObject>(IController->GetTargetInteractable());
		if (interactable)
		{
			//Pickup code goes here
			interactable->Interact(IController);
		}
	}
}


void AInteractableCharacter::Tick(float delta_time)
{
	Super::Tick(delta_time);

	//Can these both be merged into one?
	UpdateManualPickup();
	UpdateAutomaticPickup();
}

void AInteractableCharacter::UpdateManualPickup()
{
	FHitResult hit;
	int32 Range = 500;
	FVector StartTrace = FollowCamera->GetComponentLocation();
	FVector EndTrace = (FollowCamera->GetForwardVector() * Range) + StartTrace;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	ABaseController* IController = Cast<ABaseController>(GetController());

	if (IController)
	{
		// Check if something is hit
		if (GetWorld()->LineTraceSingleByChannel(hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			// Cast the actor to AInteractable
			AInteractableObject* interactable_actor = Cast<AInteractableObject>(hit.GetActor());
			// If the cast is successful
			if (interactable_actor)
			{
				//Ie have we hovered over a new item?
				if (interactable_actor != IController->GetTargetInteractable())
				{
					FString str = "Hovered Over Item [ " +  interactable_actor->GetName() + " ]";
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, str);
					
				}
				IController->SetTargetInteractable(interactable_actor);
				return;
			}
		}
		//Not hovering over anything within our given range

		IController->SetTargetInteractable(nullptr);
	}
}

void AInteractableCharacter::UpdateAutomaticPickup()
{
	//Get all actors within our loot radius
	TArray<AActor*> actors;
	m_loot_collider->GetOverlappingActors(actors);

	ABaseController* IController = Cast <ABaseController>(GetController());
	if (!IController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Can't find Base Controller.."));
		return;
	}


	for (int i = 0; i < actors.Num(); ++i)
	{
		//Attempt to cast to an automatic class
		AAutoLootObject* const auto_loot_actor = Cast<AAutoLootObject>(actors[i]);
		if (auto_loot_actor != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Auto-Loot Object Found Within Range"));
			auto_loot_actor->Collect(IController);
			
			//actor->CollectDefaultSubobjects(IController);
		}
	}

}