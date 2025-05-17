// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyFactory.h"
#include "Character/TDRPGEnemy.h"

#include "TopDownRPG/TopDownRPG.h"


AEnemyFactory::AEnemyFactory()
{
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FClassFinder<ATDRPGEnemy> tempEnemy(TEXT("Blueprint'/Game/2-Blueprints/Enemy/BP_TDRPGEnemy.BP_TDRPGEnemy_C'"));
	if(tempEnemy.Succeeded())
	{
		enemyFactory = tempEnemy.Class;
	}
}

void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	float delayTime = FMath::FRandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(
		spawnTimer, 
		this,
		&AEnemyFactory::Spawn,
		delayTime, 
		false
	);
}

void AEnemyFactory::Spawn()
{
	PRINT_LOG(TEXT("Spawn Enemy"));

	GetWorld()->SpawnActor(enemyFactory);

	float delayTime = FMath::FRandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(
		spawnTimer,
		this,
		&AEnemyFactory::Spawn,
		delayTime,
		false
	);
}


