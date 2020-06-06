// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Engine.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInteractionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	this->SetAlignmentInViewport({ 0.5, 0.5 });
	show_next_frame = false;

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
	if (show_next_frame)
	{
		show_next_frame = false;
		this->SetUIVisibility(ESlateVisibility::Visible);
	}

	//Get player on tick
	ABaseController* const player_controller = Cast<ABaseController>(UGameplayStatics::GetPlayerController(this, 0));
	if (player_controller)
	{
		//If we have a interactable and it is one thats UI should be visible
		if (player_controller->GetInteractableWidgetEnabled())
		{
			this->UpdateUI(player_controller);
			show_next_frame = true;
		}
		else
		{
			this->SetUIVisibility(ESlateVisibility::Hidden);
		}
	}
	//Do any other update functions within the blueprint
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInteractionWidget::UpdateUI(ABaseController* const player_controller)
{
	//Update Text within header
	if (HeaderText) HeaderText->SetText(FText::FromString(player_controller->GetInteractableString()));

	if (HeaderText) HeaderText->SetColorAndOpacity(player_controller->GetInteractableColour());
	//Set our GUI pos to match the location of the interactable
	FVector2D screen_pos = player_controller->GetInteractableScreenspaceCoord();

	//Constrain GUI to the bounds of the viewport (+/- Some form of border)

	
	FVector2D widget_size = this->GetDesiredSize();
	FVector2D viewport_size;
	GEngine->GameViewport->GetViewportSize(viewport_size);
	float border = viewport_size.X * 0.05f;

	float bottom_bound = viewport_size.Y - border - (widget_size.Y*0.5f);
	float top_bound = border;
	float left_bound = border + (widget_size.X*0.5f);
	float right_bound = viewport_size.X - border - (widget_size.X*0.5f);


	if (screen_pos.Y > bottom_bound) screen_pos.Y = bottom_bound;
	if (screen_pos.Y < top_bound) screen_pos.Y = top_bound;

	if (screen_pos.X < left_bound) screen_pos.X = left_bound;
	if (screen_pos.X > right_bound) screen_pos.X = right_bound;

	this->SetPositionInViewport(screen_pos);
}

void UInteractionWidget::SetUIVisibility(ESlateVisibility bl)
{
	if (Root && Root->Visibility != bl)
	{
		Root->SetVisibility(bl);
	}
}