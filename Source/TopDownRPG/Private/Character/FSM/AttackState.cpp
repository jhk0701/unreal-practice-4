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
	ATDRPGEnemy* Owner = Machine->GetOwnerEnemy();
	UEnemyAttack* Attack = Owner->AttackComp;
	
	// TODO : 사망했는지 확인
	ATDRPGPlayer* Target = Owner->Target;

	// 공격 가능한지 확인 : 거리 확인
	FVector TargetLoc = Target->GetActorLocation();
	FVector Dir = TargetLoc - Owner->GetActorLocation();
	float Range = Attack->GetAttackRange();
	
	if (Dir.SquaredLength() > Range * Range && !Attack->IsAttacking())
	{
		Machine->Transition(EEnemyState::Move); // 거리가 멀면 쫓기
	}
	else
		Attack->Attack(); // 거리 내라면 공격
}
