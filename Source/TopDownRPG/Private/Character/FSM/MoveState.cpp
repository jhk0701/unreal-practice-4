// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSM/MoveState.h"
#include "Character/EnemyFSM.h"
#include "Character/TDRPGEnemy.h"
#include "Character/TDRPGPlayer.h"
#include "Character/EnemyMove.h"

void UMoveState::Enter()
{
	Super::Enter();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Move State"));
}

void UMoveState::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	FVector dir = machine->owner->target->GetActorLocation() - machine->owner->GetActorLocation();
	float tolerance = machine->owner->moveComp->ToleranceToTarget;

	if (dir.SquaredLength() > tolerance * tolerance)
	{
		dir = machine->owner->moveComp->Speed * DeltaTime * dir.GetSafeNormal();
		machine->owner->moveComp->MoveTo(dir);
	}
	else
		machine->Transition(EEnemyState::Attack);
}
