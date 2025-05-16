// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSM/AttackState.h"

void UAttackState::Enter()
{
	Super::Enter();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Attack State"));
}
