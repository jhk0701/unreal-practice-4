// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerManager.h"
#include "Core/GameDataManager.h"
#include "Data/LevelingDataRow.h"

#include "Player/Inventory.h"
#include "Player/QuickSlot.h"
#include "Player/Equipment.h"

#include "Item/IngredientItem.h"
#include "Item/ConsumeItem.h"
#include "Item/EquipmentItem.h"

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

	// TODO: 테스트 코드 삭제
	UGameInstance* GameInst = GetGameInstance();

	// 테스트용 일반 아이템
	UIngredientItem* TestIngre_1 = NewObject<UIngredientItem>();
	UIngredientItem* TestIngre_2 = NewObject<UIngredientItem>();
	UIngredientItem* TestIngre_3 = NewObject<UIngredientItem>();

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
}

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
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();

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
