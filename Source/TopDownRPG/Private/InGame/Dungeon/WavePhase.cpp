// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/WavePhase.h"
#include "Core/DungeonGameState.h"

void UWavePhase::Enter()
{
	ADungeonGameState* gameState = Cast<ADungeonGameState>(state);
	
	// TODO : 현재 웨이브에 따른 몬스터 생성
	for (int32 i = 0; i < gameState->numberOfEnemy; i++)
		gameState->SpawnEnemy();
	
}
