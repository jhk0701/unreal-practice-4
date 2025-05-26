// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/StartPhase.h"
#include "Core/DungeonGameState.h"

void UStartPhase::Enter()
{
	Super::Enter();

	ADungeonGameState* gameState = Cast<ADungeonGameState>(state);

	// TODO : 현재 스테이지의 웨이브 데이터 받아오기
	
	// 초기화
	gameState->CurWaveIdx = 0;

	gameState->Transition(EPhaseType::Wave);
}
