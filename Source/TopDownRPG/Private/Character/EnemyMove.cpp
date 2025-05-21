// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/EnemyMove.h"

UEnemyMove::UEnemyMove()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyMove::MoveTo(const FVector& Direction)
{
	velocity = Direction;

	AActor* owner = GetOwner();
	FVector loc = owner->GetActorLocation() + Direction;
	owner->SetActorLocation(loc);
	owner->SetActorRotation(Direction.GetSafeNormal().ToOrientationQuat());
}

void UEnemyMove::StopAtLocation()
{
	velocity = FVector::ZeroVector;
}

