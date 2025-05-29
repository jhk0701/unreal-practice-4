// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/StartPhase.h"
#include "Core/DungeonGameState.h"

void UStartPhase::Enter()
{
	Super::Enter();

	ADungeonGameState* GameState = Cast<ADungeonGameState>(State);
	
	// 초기화
	GameState->CurStageID = TEXT("1001"); // TODO : 스테이지 ID 매직넘버 제거
	GameState->CurWaveIdx = 0;

	GameState->Transition(EPhaseType::Wave);
}
