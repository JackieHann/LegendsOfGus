// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"
#include "InteractableObject.h"

ABaseController::ABaseController()
	: m_targetted_interactable(nullptr)
{
}

//Fnction that converts an interactables current world position to screen coordinates
FVector2D ABaseController::GetInteractableScreenspaceCoord()
{
	//So, whenever we come in here...
	//Do we have an interactable?
	const FVector2D zero = { 0.0, 0.0 };
	if (!HasTargetInteractable()) return zero;

	//So we have an interactable, convert its world position to a screen position?
	FVector target_world_pos = this->m_targetted_interactable->GetWorldPos();

	//Allow interactables to have variable height for customization
	target_world_pos += this->m_targetted_interactable->GetOffset();

	FVector2D return_world_pos;
	this->ProjectWorldLocationToScreen(target_world_pos, return_world_pos);

	return return_world_pos;

}

bool ABaseController::GetInteractableWidgetEnabled()
{
	return (this->HasTargetInteractable() ? this->m_targetted_interactable->GetWidgetEnabled() : false);
}

FString ABaseController::GetInteractableString()
{
	//So, whenever we come in here...
	//Do we have an interactable?
	const FString empty = "";
	if(!GetInteractableWidgetEnabled())	return empty; 

	return this->m_targetted_interactable->GetInteractText();
}

void ABaseController::SetTargetInteractable(AInteractableObject* obj)
{
	m_targetted_interactable = obj;
}
bool ABaseController::HasTargetInteractable()
{
	return(this->m_targetted_interactable != nullptr);
}

AInteractableObject* ABaseController::GetTargetInteractable()
{
	return (this->m_targetted_interactable);
}