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

#include "Item/ItemBase.h"
#include "Item/ConsumeItem.h"
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
	Lv = PlayerData->CharLv;

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

	Exp = MakeUnique<FStatus>(MaxExp, PlayerData->CharExp);
	CurrencyGold = MakeUnique<FCurrency>(PlayerData->Gold);

	Exp->OnValueChanged.AddUObject(this, &UPlayerManager::CheckExp);


	// TODO: 테스트 코드 삭제
	UGameInstance* GameInst = GetGameInstance();

	// 테스트용 일반 아이템
	UItemBase* TestIngre_1 = NewObject<UItemBase>();
	UItemBase* TestIngre_2 = NewObject<UItemBase>();
	UItemBase* TestIngre_3 = NewObject<UItemBase>();

	TestIngre_1->Initialize(TEXT("0001"), GameInst, 5);
	TestIngre_2->Initialize(TEXT("0002"), GameInst, 10);
	TestIngre_3->Initialize(TEXT("0003"), GameInst, 20);

	Inventory->AddItem(TestIngre_1);
	Inventory->AddItem(TestIngre_2);
	Inventory->AddItem(TestIngre_3);

	// 테스트용 소비 아이템
	UConsumeItem* TestConsume = NewObject<UConsumeItem>();
	TestConsume->Initialize(TEXT("0001"), GameInst, 30);

	Inventory->AddItem(TestConsume);

	// 테스트용 장비 아이템 지급
	UEquipmentItem* TestEquip = NewObject<UEquipmentItem>();
	TestEquip->Initialize(TEXT("0001"), GameInst, 1);

	Inventory->AddItem(TestEquip);

	// 테스트용 무기 아이템 지급
	UWeaponItem* TestWeapon = NewObject<UWeaponItem>();
	TestWeapon->Initialize(TEXT("0001"), GameInst, 1);

	Inventory->AddItem(TestWeapon);
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
