// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAttack.h"
#include "Core/TDRPGPlayerController.h"
#include <EnhancedInputComponent.h>


UPlayerAttack::UPlayerAttack()
{
}

void UPlayerAttack::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->AttackNormalAction, ETriggerEvent::Triggered, this, &UPlayerAttack::InputAttack);
}

void UPlayerAttack::InputAttack(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, TEXT("Player Normal Attack"));
}
