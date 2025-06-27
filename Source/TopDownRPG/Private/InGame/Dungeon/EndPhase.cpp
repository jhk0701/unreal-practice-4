// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/EndPhase.h"
#include "InGame/Dungeon/DungeonGameState.h"

#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Core/PlayerDataManager.h"
#include "Core/PlayerManager.h"
#include "Core/UIManager.h"
#include "Data/StageDataRow.h"

#include "UI/TDRPGUWStageResult.h"

#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>


void UEndPhase::Enter()
{
	UGameInstance* GameInst = State->GetGameInstance();
	ADungeonGameState* GameState = Cast<ADungeonGameState>(State);
	// GameState->EnemyCount
	bool bIsCleared = GameState->StageResult == EStageResult::Cleared;

	UPlayerManager* Player = GameInst->GetSubsystem<UPlayerManager>();
	// 클리어 시, 스테이지 보상
	if (bIsCleared)
	{
		// 현재 스테이지 정보 불러오기
		UGameDataManager* GameData = GameInst->GetSubsystem<UGameDataManager>();
		FStageDataRow* StageData = GameData->GetRow<FStageDataRow>(ETableType::Stage, *GameState->CurStageId);

		// 골드 보상 수령
		Player->AddGold(StageData->GoldReward);
		Player->AddExp(StageData->ExpReward);
	}

	// 스테이지 종료 UI
	UUIManager* UI = GameInst->GetSubsystem<UUIManager>();

	if (UTDRPGUWStageResult* ResultUI = UI->GetUI<UTDRPGUWStageResult>())
	{
		ResultUI->SetResult(bIsCleared);
		ResultUI->Open();
	}

	// 스테이지 종료 시 저장
	GameInst->GetSubsystem<UPlayerDataManager>()->SaveData(Player);
}
