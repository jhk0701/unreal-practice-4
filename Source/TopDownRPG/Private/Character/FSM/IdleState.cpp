// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSM/IdleState.h"

void UIdleState::Enter()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Idle State"));
}
