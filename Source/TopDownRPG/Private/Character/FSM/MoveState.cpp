// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSM/MoveState.h"
#include "Character/EnemyFSM.h"
#include "Character/TDRPGEnemy.h"
#include "Character/TDRPGPlayer.h"
#include "Character/EnemyMove.h"
#include "Character/EnemyAttack.h"

#include "TopDownRPG/TopDownRPG.h"

void UMoveState::Enter()
{
	Super::Enter();
}

void UMoveState::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	ATDRPGEnemy* Owner = Machine->GetOwnerEnemy();

	FVector TargetLoc = Owner->Target->GetActorLocation();
	FVector OwnerLoc = Owner->GetActorLocation();

	FVector Dir = TargetLoc - OwnerLoc;
	float Range = Owner->AttackComp->GetAttackRange();

	if (Dir.SquaredLength() > Range * Range)
	{
		Dir = Owner->MoveComp->Speed * DeltaTime * Dir.GetSafeNormal();
		Owner->MoveComp->MoveTo(Dir);
	}
	else
	{
		Machine->Transition(EEnemyState::Attack);
		Owner->MoveComp->StopAtLocation();
	}
}
