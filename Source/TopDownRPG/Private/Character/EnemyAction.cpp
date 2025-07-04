// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAction.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/EnemyAnim.h"

#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"

// Sets default values for this component's properties
UEnemyAction::UEnemyAction()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyAction::BeginPlay()
{
	Super::BeginPlay();

	bIsAttacking = false;
	CurCooldown = .0f;

	Enemy = Cast<ATDRPGEnemy>(GetOwner());

}

void UEnemyAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAttacking)
	{
		CurCooldown -= DeltaTime;
		
		if (CurCooldown <= .0f)
			bIsAttacking = false;
	}
}

void UEnemyAction::InvokeAttack()
{
	if (bIsAttacking)
		return;

	bIsAttacking = true;
	CurCooldown = AttackCooldown;

	PRINT_LOG(TEXT("Enemy Attack!"));
	Enemy->AnimInst->PlayAttack(0);
}

void UEnemyAction::InvokeSkill(int32 InIndex)
{
}

