// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInteractionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	this->SetAlignmentInViewport({ 0.5, 0.5 });

}
void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInteractionWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Do any other update functions within the blueprint
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Get player on tick
	ABaseController* const player_controller = Cast<ABaseController>(UGameplayStatics::GetPlayerController(this, 0));
	if (player_controller)
	{
		//If we have a interactable and it is one thats UI should be visible
		if (player_controller->GetInteractableWidgetEnabled())
		{
			this->UpdateUI(player_controller);
			this->SetUIVisibility(ESlateVisibility::Visible);
		}
		else
		{
			this->SetUIVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UInteractionWidget::UpdateUI(ABaseController* const player_controller)
{
	//Update Text within header
	if (HeaderText) HeaderText->SetText(FText::FromString(player_controller->GetInteractableString()));

	//Set our GUI pos to match the location of the interactable
	FVector2D screen_pos = player_controller->GetInteractableScreenspaceCoord();
	this->SetPositionInViewport(screen_pos);
}

void UInteractionWidget::SetUIVisibility(ESlateVisibility bl)
{
	if (Root && Root->Visibility != bl)
	{
		Root->SetVisibility(bl);
	}
}