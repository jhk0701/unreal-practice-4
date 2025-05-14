// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TDRPGPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ATDRPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* player = GetLocalPlayer();

	if (!player) 
		return;

	if (UEnhancedInputLocalPlayerSubsystem* inputSystem = player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		if (InputContext)
			inputSystem->AddMappingContext(InputContext, 0);
	}
}
