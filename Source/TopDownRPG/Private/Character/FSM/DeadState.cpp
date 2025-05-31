// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSM/DeadState.h"
#include "Character/TDRPGEnemy.h"
#include "Character/EnemyFSM.h"


void UDeadState::Enter()
{
	Super::Enter();

	Machine->GetOwnerEnemy()->Destroy();
}
