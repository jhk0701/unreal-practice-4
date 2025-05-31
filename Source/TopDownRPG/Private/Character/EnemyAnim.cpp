// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAnim.h"
#include "Character/TDRPGEnemy.h"
#include "Character/EnemyAttack.h"
#include "Character/EnemyMove.h"
#include "Character/CharacterData.h"

void UEnemyAnim::SetAccel(const APawn* Pawn)
{
	FVector Velocity = Cast<ATDRPGEnemy>(Pawn)->MoveComp->GetVelocity();
	FVector Forward = Pawn->GetActorForwardVector();

	double Dir = FVector::DotProduct(Velocity, Forward);
	Accel = (float)FMath::Max(Dir, 0) * AccelScaler;
}

void UEnemyAnim::SetIsDead(const APawn* Pawn)
{
	if(const ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(Pawn))
	{
		bIsDead = Enemy->GetData()->bIsDead;
	}
}

void UEnemyAnim::OnAttackStarted()
{
	if (ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(TryGetPawnOwner()))
		Enemy->AttackComp->ActivateHitCollider(true);
}

void UEnemyAnim::OnAttackEnded()
{
	if (ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(TryGetPawnOwner()))
		Enemy->AttackComp->ActivateHitCollider(false);
}
