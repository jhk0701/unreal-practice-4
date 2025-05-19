// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DungeonGameState.h"
#include "Character/TDRPGEnemy.h"

#include "TopDownRPG/TopDownRPG.h"

ADungeonGameState::ADungeonGameState()
{
	// TODO : 데이터 기반 생성으로 변경
	ConstructorHelpers::FClassFinder<ATDRPGEnemy> tempEnemy(TEXT("Blueprint'/Game/2-Blueprints/Enemy/BP_TDRPGEnemy.BP_TDRPGEnemy_C'"));
	if (tempEnemy.Succeeded())
		enemyFactory = tempEnemy.Class;
}

void ADungeonGameState::BeginPlay()
{
	Super::BeginPlay();

	// TODO : 데이터 기반 생성할 것
	for (int32 i = 0; i < numberOfEnemy; i++)
	{
		SpawnEnemy();
	}
}

void ADungeonGameState::SpawnEnemy()
{
	if (!enemyFactory)
	{
		PRINT_LOG(TEXT("Enemy to spawn is null."));
		return;
	}

	FVector spawnLoc = spawnPoint;
	spawnLoc.X += FMath::RandRange(-spawningRadius, spawningRadius);
	spawnLoc.Y += FMath::RandRange(-spawningRadius, spawningRadius);
	
	FTransform spawnTransform;
	spawnTransform.SetLocation(spawnLoc);
	spawnTransform.SetRotation(FQuat::Identity);

	GetWorld()->SpawnActor<AActor>(enemyFactory, spawnTransform);

	++enemyCount;
}

void ADungeonGameState::OnEnemyDead()
{
	if (enemyCount == 0)
		return;

	--enemyCount;

	if (enemyCount == 0)
	{
		PRINT_LOG(TEXT("Game State Ended"));
	}
}
