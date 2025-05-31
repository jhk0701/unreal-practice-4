// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/EnemyMove.h"

UEnemyMove::UEnemyMove()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyMove::MoveTo(const FVector& Direction)
{
	Velocity = Direction;

	AActor* Owner = GetOwner();
	FVector Loc = Owner->GetActorLocation() + Direction;
	Owner->SetActorLocation(Loc);
	Owner->SetActorRotation(Direction.GetSafeNormal().ToOrientationQuat());
}

void UEnemyMove::StopAtLocation()
{
	Velocity = FVector::ZeroVector;
}

