// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/EndPhase.h"
#include "InGame/Dungeon/DungeonHUD.h"

#include "InGame/Dungeon/DungeonGameState.h"
#include "Core/GameDataManager.h"
#include "Core/PlayerManager.h"
#include "Data/StageDataRow.h"

#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>

#include "TopDownRPG/TopDownRPG.h"

void UEndPhase::Enter()
{
	ADungeonGameState* GameState = Cast<ADungeonGameState>(State);
	
	// 클리어 시, 스테이지 보상
	if (GameState->StageResult == EStageResult::Cleared) 
	{
		UGameInstance* GameInstance = State->GetGameInstance();

		// 현재 스테이지 정보 불러오기
		UGameDataManager* GameData = GameInstance->GetSubsystem<UGameDataManager>();
		FStageDataRow* StageData = GameData->GetRow<FStageDataRow>(ETableType::Stage, *GameState->CurStageId);

		UPlayerManager* PlayerData = GameInstance->GetSubsystem<UPlayerManager>();

		// 골드 보상 수령
		PRINT_LOG(TEXT("Cur Lv : %u, Exp : %u, Gold : %u"), PlayerData->Lv, PlayerData->Exp->GetCurrentValue(), PlayerData->CurrencyGold->GetCurrency());

		PlayerData->CurrencyGold->Add(StageData->GoldReward);
		PlayerData->Exp->Add(StageData->ExpReward);

		PRINT_LOG(TEXT("After Lv : %u, Exp : %u, Gold : %u"), PlayerData->Lv, PlayerData->Exp->GetCurrentValue(), PlayerData->CurrencyGold->GetCurrency());
	}

	// 스테이지 종료 UI
	APlayerController* controller = UGameplayStatics::GetPlayerController(State->GetWorld(), 0);
	
	if(ADungeonHUD* hud = Cast<ADungeonHUD>(controller->GetHUD()))
	{
		hud->ShowResultUI();
	}

}
