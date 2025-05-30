// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/WavePhase.h"
#include "Core/DungeonGameState.h"
#include "Core/GameDataManager.h"
#include "Data/StageDataRow.h"

void UWavePhase::Enter()
{
	ADungeonGameState* GameState = Cast<ADungeonGameState>(State);

	// 현재 스테이지의 웨이브 데이터 받아오기
	UGameDataManager* GameData = GameState->GetGameInstance()->GetSubsystem<UGameDataManager>();
	FStageDataRow* StageData = GameData->GetRow<FStageDataRow>(ETableType::Stage, *GameState->CurStageId);

	// 데이터에 따라 적 소환
	FInnerIntArray EnemyList = StageData->EnemyListPerWave[GameState->CurWaveIdx];
	FInnerIntArray Spawn = StageData->EnemySpawnPerWave[GameState->CurWaveIdx];
	for (int32 i = 0; i < EnemyList.Array.Num(); ++i)
	{
		for (int32 j = 0; j < Spawn.Array[i]; j++)
			GameState->SpawnEnemy(FString::Printf(TEXT("%d"), EnemyList.Array[i]));
	}
	
}

void UWavePhase::Exit()
{
	ADungeonGameState* GameState = Cast<ADungeonGameState>(State);
	++GameState->CurWaveIdx;
}
