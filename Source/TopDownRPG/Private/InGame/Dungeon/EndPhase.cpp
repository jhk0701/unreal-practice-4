// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/EndPhase.h"
#include <Kismet/GameplayStatics.h>
#include "Core/DungeonGameMode.h"
#include "Core/DungeonGameState.h"

void UEndPhase::Enter()
{

	// TODO : UI 띄우기

	// 스테이지 종료 UI
	// 스테이지 보상

	// 로비로 이동
	ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(state->GetWorld()));
	gameMode->GoToLobby();
}
