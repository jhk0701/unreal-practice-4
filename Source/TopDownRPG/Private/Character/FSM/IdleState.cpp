// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/FSM/IdleState.h"
#include "Character/EnemyFSM.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Kismet/GameplayStatics.h"

void UIdleState::Enter()
{
	Super::Enter();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Idle State"));

	// TODO : 하드코딩 제거
	machine->owner->target = Cast<ATDRPGPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	machine->Transition(EEnemyState::Move);
}
