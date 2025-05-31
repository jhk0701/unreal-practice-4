// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TDGameState.h"
#include "DungeonGameState.generated.h"

class UBasePhase;

UENUM(BlueprintType)
enum class EPhaseType : uint8
{
	Start,
	Wave,
	End,
};

UENUM(BlueprintType)
enum class EStageResult : uint8 
{
	Cleared,
	Failed
};
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ADungeonGameState : public ATDGameState
{
	GENERATED_BODY()

	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Result)
	EStageResult StageResult = EStageResult::Cleared;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wave)
	FString CurStageId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wave)
	int32 CurWaveIdx = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawn")
	TSubclassOf<class ATDRPGEnemy> enemyFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemySpawn")
	int32 EnemyCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawn|Setting")
	FVector spawnPoint = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawn|Setting")
	float spawningRadius = 500.f;


protected:
	UPROPERTY()
	TObjectPtr<UBasePhase> CurPhase;

	UPROPERTY()
	TMap<EPhaseType, UBasePhase*> PhaseMap;

public:
	ADungeonGameState();
	virtual void BeginPlay() override;

	void Transition(EPhaseType InPhase);

	void SpawnEnemy(const FString& EnemyID);
	
	const inline int32 GetEnemyCount() { return EnemyCount; }
	
	void OnEnemyDead();

	void ProceedWave();

	void FinishStage(EStageResult InResult);

};
