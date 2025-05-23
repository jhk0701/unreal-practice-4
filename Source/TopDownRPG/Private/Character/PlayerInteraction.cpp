// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInteraction.h"
#include "Core/TDRPGPlayerController.h"
#include <EnhancedInputComponent.h>

#include "TopDownRPG/TopDownRPG.h"

void UPlayerInteraction::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->InteractAction, ETriggerEvent::Started, this, &UPlayerInteraction::InvokeInteract);
}

void UPlayerInteraction::InvokeInteract(const FInputActionValue& Value)
{
	PRINT_LOG(TEXT("Interact"));
}
