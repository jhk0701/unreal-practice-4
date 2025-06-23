// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerManager.h"

#include "Player/Inventory.h"
#include "Player/QuickSlot.h"
#include "Player/Equipment.h"

#include <Kismet/GameplayStatics.h>
#include "TDRPGEnum.h"

#include "Core/GameDataManager.h"
#include "Data/CharacterDataRow.h"
#include "Data/LevelingDataRow.h"

#include "TopDownRPG/TopDownRPG.h"


void UPlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitManager();
}

void UPlayerManager::InitManager()
{
	Inventory = NewObject<UInventory>();	// 인벤토리 초기화
	QuickSlot = NewObject<UQuickSlot>();	// 퀵슬롯 초기화
	Equipment = NewObject<UEquipment>();	// 장비창 초기화
}

void UPlayerManager::SetPlayerData(UTDRPGSaveGame* InPlayerData)
{
	if (!InPlayerData)
		return;

	PlayerData = InPlayerData;
	
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FCharacterDataRow* CharData = GameData->GetRow<FCharacterDataRow>(ETableType::Character, PlayerData->ClassID);
	ClassName = CharData->CharName;

	// 레벨링 데이터 불러오기
	InitLvAndExp(PlayerData->CharLv, PlayerData->CharExp);

	if (CurrencyGold)
		CurrencyGold.Reset();

	CurrencyGold = MakeUnique<FCurrency>(PlayerData->Gold);
}

void UPlayerManager::InitLvAndExp(uint32 InLv, uint32 InExp)
{
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();

	TArray<int32> Leveling;
	GameData->GetLeveling(PlayerData->ClassID, Lv, Leveling);

	// Exp 파트 더하기
	uint32 MaxExp = 0;
	int32 Cnt = Leveling.Num();
	for (int32 i = 0; i < Cnt; i++)
	{
		FString Key = GameData->GetLevelingKey(PlayerData->ClassID, i);
		FLevelingDataRow* LevelData = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, *Key);

		MaxExp += LevelData->ExpDemand;
	}

	if (Exp)
		Exp.Reset();

	Exp = MakeUnique<FStatus>(MaxExp, PlayerData->CharExp);

	Exp->OnValueChanged.AddUObject(this, &UPlayerManager::CheckExp);
}


void UPlayerManager::AddExp(uint32 Value)
{
	Exp->Add(Value);
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

	int32 Index = GameData->GetLevelingIndex(PlayerData->ClassID, Lv);
	FString Key = GameData->GetLevelingKey(PlayerData->ClassID, Index);
	FLevelingDataRow* LevelData = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, *Key);

	uint32 MaxExp = Exp->GetMaxValue() + LevelData->ExpDemand;
	Exp->ChangeMaxValue(MaxExp, 0);
}

void UPlayerManager::AddGold(uint32 Value)
{
	CurrencyGold->Add(Value);
}
