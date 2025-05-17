// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FSM/AttackState.h"
#include "Character/EnemyFSM.h"
#include "Character/TDRPGEnemy.h"
#include "Character/TDRPGPlayer.h"
#include "Character/EnemyAttack.h"

void UAttackState::Enter()
{
	Super::Enter();


}

void UAttackState::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	// 공격 행동
	ATDRPGEnemy* owner = machine->GetOwnerEnemy();
	UEnemyAttack* attack = owner->attackComp;
	
	// TODO : 사망했는지 확인
	ATDRPGPlayer* target = owner->target;

	// 공격 가능한지 확인
	if (attack->IsAttackable())
		attack->Attack();
	else
	{
		// 거리 확인
		FVector targetLoc = target->GetActorLocation();
		FVector dir = targetLoc - owner->GetActorLocation();
		float range = attack->GetAttackRange();

		// 거리가 멀면 쫓기
		if (dir.SquaredLength() > range * range)
			machine->Transition(EEnemyState::Move);
	}
}
