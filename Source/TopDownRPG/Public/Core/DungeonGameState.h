// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TDGameState.h"
#include "DungeonGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ADungeonGameState : public ATDGameState
{
	GENERATED_BODY()

	
protected:
	// 적 캐릭터 관리용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy)
	int32 enemyCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawn)
	TSubclassOf<class ATDRPGEnemy> enemyFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawn|Setting")
	int32 numberOfEnemy = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawn|Setting")
	FVector spawnPoint = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawn|Setting")
	float spawningRadius = 500.f;

public:
	ADungeonGameState();
	virtual void BeginPlay() override;

	void SpawnEnemy();
	int32 GetEnemyCount() { return enemyCount; }
	void OnEnemyDead();

};
