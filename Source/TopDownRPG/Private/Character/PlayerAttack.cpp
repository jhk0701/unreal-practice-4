// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAttack.h"
#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"
#include <EnhancedInputComponent.h>
#include "Character/CharacterStatus.h"


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
	InvokeAttack();
}

void UPlayerAttack::InvokeAttack()
{
	me->InvokeAttackDelegate(); // 이동 기능은 꺼질 것

	// me->GetStatus()->Stat[EStatus::Health]->Subtract(10);
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("remain hp : %d"), (int32)me->GetStatus()->Stat[EStatus::Health]->GetCurrentValue()));
}
