// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

ABaseController::ABaseController()
	: m_targetted_interactable(nullptr)
{
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