// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerManager.h"
#include "Core/GameDataManager.h"
#include "Data/LevelingDataRow.h"

#include "Player/Inventory.h"

#include "Item/IngredientItem.h"
#include "Data/ItemDataRow.h"

#include "TopDownRPG/TopDownRPG.h"


void UPlayerManager::LoadData()
{
	// TODO : 데이터 불러오기
	PlayerData = MakeUnique<FPlayerData>();

	PlayerData->PlayerID = TEXT("1");
	PlayerData->CharID = TEXT("1001");
	PlayerData->CharLv = 5;
	PlayerData->CharExp = 0;
	PlayerData->Gold = uint32(100);

	Lv = PlayerData->CharLv;

	// 레벨링 데이터 불러오기
	UGameInstance* GameInst = GetGameInstance();
	UGameDataManager* GameData = GameInst->GetSubsystem<UGameDataManager>();

	TArray<int32> Leveling;
	GameData->GetLeveling(PlayerData->CharID, Lv, Leveling);

	// Exp 파트 더하기
	uint32 MaxExp = 0;
	int32 Cnt = Leveling.Num();
	for (int32 i = 0; i < Cnt; i++)
	{
		FString Key = GameData->GetLevelingKey(PlayerData->CharID, i);
		FLevelingDataRow* LevelData = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, *Key);
		
		MaxExp += LevelData->ExpDemand;
	}

	Exp = MakeUnique<Status>(MaxExp, PlayerData->CharExp);
	CurrencyGold = MakeUnique<Currency>(PlayerData->Gold);

	Exp->OnValueChanged.AddUObject(this, &UPlayerManager::CheckExp);

	Inventory = NewObject<UInventory>();
	Inventory->Initialize();

	// TODO: 테스트 코드 삭제
	FName IngreID1 = TEXT("0001");
	FName IngreID2 = TEXT("0002");
	FName IngreID3 = TEXT("0003");

	UIngredientItem* Ingre1 = NewObject<UIngredientItem>();
	UIngredientItem* Ingre2 = NewObject<UIngredientItem>();
	UIngredientItem* Ingre3 = NewObject<UIngredientItem>();

	Ingre1->Initialize(IngreID1, GameInst, 5);
	Ingre2->Initialize(IngreID2, GameInst, 10);
	Ingre3->Initialize(IngreID3, GameInst, 20);

	Inventory->AddItem(Ingre1);
	Inventory->AddItem(Ingre2);
	Inventory->AddItem(Ingre3);
}

void UPlayerManager::SaveData()
{
	PlayerData->CharLv = Lv;
	PlayerData->CharExp = Exp->GetCurrentValue();

	PlayerData->Gold = CurrencyGold->GetCurrency();
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
	FString Key = GameData->GetLevelingKey(PlayerData->CharID, Lv);
	FLevelingDataRow* LevelData = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, *Key);

	uint32 MaxExp = Exp->GetMaxValue() + LevelData->ExpDemand;
	Exp->ChangeMaxValue(MaxExp, 0);

}
