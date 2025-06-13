// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/EndPhase.h"
#include "InGame/Dungeon/DungeonGameState.h"

#include "Core/GameDataManager.h"
#include "Core/PlayerManager.h"
#include "Core/UIManager.h"
#include "Data/StageDataRow.h"

#include "UI/TDRPGUWStageResult.h"

#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>


void UEndPhase::Enter()
{
	UGameInstance* GameInstance = State->GetGameInstance();
	ADungeonGameState* GameState = Cast<ADungeonGameState>(State);
	// GameState->EnemyCount
	bool bIsCleared = GameState->StageResult == EStageResult::Cleared;

	// 클리어 시, 스테이지 보상
	if (bIsCleared)
	{
		// 현재 스테이지 정보 불러오기
		UGameDataManager* GameData = GameInstance->GetSubsystem<UGameDataManager>();
		FStageDataRow* StageData = GameData->GetRow<FStageDataRow>(ETableType::Stage, *GameState->CurStageId);

		UPlayerManager* PlayerData = GameInstance->GetSubsystem<UPlayerManager>();

		// 골드 보상 수령
		PlayerData->CurrencyGold->Add(StageData->GoldReward);
		PlayerData->Exp->Add(StageData->ExpReward);
	}

	// 스테이지 종료 UI
	UUIManager* UI = GameInstance->GetSubsystem<UUIManager>();

	if (UTDRPGUWStageResult* ResultUI = UI->GetUI<UTDRPGUWStageResult>())
	{
		ResultUI->SetResult(bIsCleared);
		ResultUI->Open();
	}
}
