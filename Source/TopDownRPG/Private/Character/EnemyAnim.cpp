// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAnim.h"
#include "Character/TDRPGEnemy.h"
#include "Character/EnemyAttack.h"
#include "Character/EnemyMove.h"
#include "Character/CharacterStatus.h"

void UEnemyAnim::SetAccel(const APawn* Pawn)
{
	FVector velocity = Cast<ATDRPGEnemy>(Pawn)->moveComp->GetVelocity();
	FVector forward = Pawn->GetActorForwardVector();

	double dir = FVector::DotProduct(velocity, forward);
	Accel = (float)FMath::Max(dir, 0) * AccelScaler;
}

void UEnemyAnim::SetIsDead(const APawn* Pawn)
{
	if(const ATDRPGEnemy* enemy = Cast<ATDRPGEnemy>(Pawn))
	{
		bIsDead = enemy->GetStatus()->bIsDead;
	}
}

void UEnemyAnim::OnAttackStarted()
{
	if (ATDRPGEnemy* enemy = Cast<ATDRPGEnemy>(TryGetPawnOwner()))
		enemy->attackComp->ActivateHitCollider(true);
}

void UEnemyAnim::OnAttackEnded()
{
	if (ATDRPGEnemy* enemy = Cast<ATDRPGEnemy>(TryGetPawnOwner()))
		enemy->attackComp->ActivateHitCollider(false);
}
