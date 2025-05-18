// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/EnemyMove.h"

UEnemyMove::UEnemyMove()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyMove::MoveTo(const FVector& Direction)
{
	AActor* owner = GetOwner();
	FVector loc = owner->GetActorLocation() + Direction;
	owner->SetActorLocation(loc);
	
	owner->SetActorRotation(Direction.GetSafeNormal().ToOrientationQuat());
}

