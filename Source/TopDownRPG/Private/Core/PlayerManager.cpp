// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerManager.h"
#include "Core/TDRPGSaveGame.h"

#include <Kismet/GameplayStatics.h>
#include "TDRPGEnum.h"

#include "Core/GameDataManager.h"
#include "Data/CharacterDataRow.h"
#include "Data/LevelingDataRow.h"

#include "Core/ItemFactory.h"
#include "Player/Inventory.h"
#include "Player/QuickSlot.h"
#include "Player/Equipment.h"

#include "Item/ItemBase.h"
#include "Item/EquipmentItem.h"
#include "Item/WeaponItem.h"

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

	// 재화 반영
	InitGold(PlayerData->Gold);

	InitInventory();
	InitEquipment();
	InitQuickSlot();
}

FString& UPlayerManager::GetClassID() const
{
	return PlayerData->ClassID;
}

void UPlayerManager::InitLvAndExp(uint32 InLv, uint32 InExp)
{
	Lv = InLv;

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

void UPlayerManager::InitGold(uint32 InGold)
{
	if (CurrencyGold)
		CurrencyGold.Reset();

	CurrencyGold = MakeUnique<FCurrency>(InGold);
}

void UPlayerManager::InitInventory()
{
	UItemFactory* ItemFactory = GetGameInstance()->GetSubsystem<UItemFactory>();

	int32 Cnt = PlayerData->Inventory.Num();
	for (int32 i = 0; i < Cnt; ++i) 
	{
		auto& ItemData = PlayerData->Inventory[i];

		if (ItemData.ItemID == CommonConst::EMPTY_ITEM_ID)
			continue;

		UItemBase* Item = ItemFactory->GetItem((ETableType)ItemData.ItemType, ItemData.ItemID, ItemData.Quantity);
		Inventory->InitInventory(i, Item);
	}
}

void UPlayerManager::InitEquipment()
{
	UItemFactory* ItemFactory = GetGameInstance()->GetSubsystem<UItemFactory>();

	int32 Cnt = PlayerData->Equipment.Num();
	for (int32 i = 0; i < Cnt; ++i) 
	{
		auto& EquipData = PlayerData->Equipment[i];
		
		if (EquipData.EquipmentID == CommonConst::EMPTY_ITEM_ID)
			continue;

		EEquipType Type = (EEquipType)EquipData.EquipType;
		UEquipmentItem* EquipItem = nullptr;

		Type == EEquipType::Weapon ? 
			EquipItem = ItemFactory->GetItem<UWeaponItem>(EquipData.EquipmentID) :
			EquipItem = ItemFactory->GetItem<UEquipmentItem>(EquipData.EquipmentID);

		if (EquipItem)
			Equipment->Equip(Type, EquipItem);
	}
}


void UPlayerManager::InitQuickSlot()
{
	int32 Cnt = PlayerData->QuickSlot.Num();
	for (int32 i = 0; i < Cnt; ++i) 
	{
		int32 Index = PlayerData->QuickSlot[i];
		if (Index >= 0)
			QuickSlot->InitSlot(Index, Cast<IQuickSlotHandler>(Inventory->Items[Index]));
	}
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
