// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerManager.h"
#include "Core/GameDataManager.h"
#include "Data/LevelingDataRow.h"

#include "TopDownRPG/TopDownRPG.h"

void UPlayerManager::LoadData()
{
	// TODO : 데이터 불러오기
	PlayerData = 
	{
		// PlayerID
		TEXT("1"),

		// Character 정보
		TEXT("1001"),
		5,
		0,

		// 재화 : 골드
		uint32(100)
	};

	Lv = PlayerData.CharLv;

	// 레벨링 데이터 불러오기
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();

	TArray<int32> Leveling;
	GameData->GetLeveling(PlayerData.CharID, Lv, Leveling);

	// Exp 파트 더하기
	uint32 MaxExp = 0;
	int32 Cnt = Leveling.Num();
	for (int32 i = 0; i < Cnt; i++)
	{
		FString Key = GameData->GetLevelingKey(PlayerData.CharID, i);
		FLevelingDataRow* LevelData = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, *Key);
		
		MaxExp += LevelData->ExpDemand;
	}

	Exp = MakeUnique<Status>(MaxExp, PlayerData.CharExp);
	CurrencyGold = MakeUnique<Currency>(PlayerData.Gold);

	Exp->OnValueChanged.AddUObject(this, &UPlayerManager::CheckExp);
}

void UPlayerManager::SaveData()
{
	PlayerData.CharLv = Lv;
	PlayerData.CharExp = Exp->GetCurrentValue();

	PlayerData.Gold = CurrencyGold->GetCurrency();
	// TODO : Save
}

void UPlayerManager::CheckExp(uint32 Max, uint32 Current)
{
	if (Current >= Max)
		LevelUp();
}

void UPlayerManager::LevelUp()
{
	++Lv;

	// 레벨링 데이터에서 새로운 레벨의 경험치 요구량 받아오기
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FString Key = GameData->GetLevelingKey(PlayerData.CharID, Lv);
	FLevelingDataRow* LevelData = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, *Key);

	uint32 MaxExp = Exp->GetMaxValue() + LevelData->ExpDemand;
	Exp->ChangeMaxValue(MaxExp, 0);

}
