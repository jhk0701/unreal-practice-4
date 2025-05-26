// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/EnemySpawner.h"

// Sets default values for this component's properties
UEnemySpawner::UEnemySpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}