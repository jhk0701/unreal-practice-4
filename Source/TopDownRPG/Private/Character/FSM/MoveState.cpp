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

	PRINT_LOG(TEXT("Move Enter"));
}

void UMoveState::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	ATDRPGEnemy* owner = machine->GetOwnerEnemy();

	FVector targetLoc = owner->target->GetActorLocation();
	FVector ownerLoc = owner->GetActorLocation();

	FVector dir = targetLoc - ownerLoc;
	float range = owner->attackComp->GetAttackRange();

	if (dir.SquaredLength() > range * range)
	{
		dir = owner->moveComp->Speed * DeltaTime * dir.GetSafeNormal();
		owner->moveComp->MoveTo(dir);
	}
	else
		machine->Transition(EEnemyState::Attack);
}
