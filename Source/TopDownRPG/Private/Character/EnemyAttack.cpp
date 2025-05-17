// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAttack.h"

#include "TopDownRPG/TopDownRPG.h"

// Sets default values for this component's properties
UEnemyAttack::UEnemyAttack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyAttack::BeginPlay()
{
	Super::BeginPlay();

	bIsAttackable = true;
	curCooldown = .0f;
}

void UEnemyAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsAttackable)
	{
		curCooldown -= DeltaTime;
		
		if (curCooldown <= .0f)
			bIsAttackable = true;
	}
}

void UEnemyAttack::Attack()
{
	if (!bIsAttackable)
		return;

	bIsAttackable = false;
	curCooldown = attackCooldown;

	PRINT_LOG(TEXT("Enemy Attack!"));
}

