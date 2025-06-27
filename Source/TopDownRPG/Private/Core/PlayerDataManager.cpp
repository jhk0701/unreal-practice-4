// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerDataManager.h"
#include "Core/PlayerManager.h"
#include "Core/TDRPGSaveGame.h"

#include "CommonConst.h"
#include "TDRPGEnum.h"

#include "Character/Status.h"
#include "Property/Currency.h"

#include "Item/ItemBase.h"
#include "Item/ConsumeItem.h"
#include "Item/EquipmentItem.h"
#include "Item/WeaponItem.h"

#include "Player/Inventory.h"
#include "Player/Equipment.h"
#include "Player/QuickSlot.h"

#include <Kismet/GameplayStatics.h>

#include <Misc/Paths.h>
#include <HAL/FileManager.h>

#include "TopDownRPG/TopDownRPG.h"


void UPlayerDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GetPlayerDatas(PlayerDataDir);
}

void UPlayerDataManager::GetPlayerDatas(TArray<FString>& OutDirectories)
{
	OutDirectories.Empty();

	// 메모하기 : 프로젝트 SaveGames 경로 찾기
	FString SaveDir = FPaths::ProjectSavedDir() / TEXT("SaveGames");

	// PRINT_LOG(TEXT("[SaveDir] %s"), *SaveDir);
	
	if (!FPaths::DirectoryExists(SaveDir))
	{
		PRINT_LOG(TEXT("There is no save directory"));
		return;
	}

	FString SaveFilePath = SaveDir / TEXT("*.sav");
	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFiles(OutDirectories, *SaveFilePath, true, false);
}

void UPlayerDataManager::CreateData(const FString& InPlayerName, const FString& InClassID)
{
	Data = Cast<UTDRPGSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDRPGSaveGame::StaticClass()));

	// 초기 데이터 생성
	Data->PlayerName = FName(InPlayerName);
	Data->ClassID = InClassID;
	Data->UserIndex = 0;
	Data->PlayerID = InPlayerName + "_" + FDateTime::Now().ToString();

	Data->CharLv = 1;
	Data->CharExp = 0;
	Data->Gold = uint32(1000);

	Data->Inventory.Init(FInventorySaveData(), UInventory::MAX_SIZE);
	Data->Equipment.Init(FEquipmentSaveData(), (int32)EEquipType::COUNT);
	Data->QuickSlot.Init(-1, UQuickSlot::MAX_SIZE);

	GetGameInstance()->GetSubsystem<UPlayerManager>()->SetPlayerData(Data);

	// 초기 세이브
	UGameplayStatics::AsyncSaveGameToSlot(Data, Data->PlayerID, Data->UserIndex);
}

void UPlayerDataManager::SaveData(const UPlayerManager* InPlayer)
{
	Data = Cast<UTDRPGSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDRPGSaveGame::StaticClass()));

	Data->PlayerName = InPlayer->PlayerData->PlayerName;
	Data->ClassID = InPlayer->PlayerData->ClassID;
	Data->UserIndex = 0;
	Data->PlayerID = InPlayer->PlayerData->PlayerID;

	Data->CharLv = InPlayer->Lv;
	Data->CharExp = InPlayer->Exp->GetCurrentValue();
	Data->Gold = InPlayer->CurrencyGold->GetCurrency();

	Data->Inventory.Init(FInventorySaveData(), UInventory::MAX_SIZE);
	Data->Equipment.Init(FEquipmentSaveData(), (int32)EEquipType::COUNT);
	Data->QuickSlot.Init(-1, UQuickSlot::MAX_SIZE);

	// Inventory
	int32 Cnt = InPlayer->Inventory->Items.Num();
	for (int32 i = 0; i < Cnt; ++i) 
	{
		UItemBase* Item = InPlayer->Inventory->Items[i];
		if (Item)
		{
			Data->Inventory[i].ItemID = Item->GetItemID();
			Data->Inventory[i].ItemType = (int32)Item->GetItemType();
			Data->Inventory[i].Quantity = Item->Quantity;
		}
		else
			Data->Inventory[i].ItemID = CommonConst::EMPTY_ITEM_ID;
	}

	// Equipment
	Cnt = (int32)EEquipType::COUNT;
	for (int32 i = 0; i < Cnt; ++i)
	{
		EEquipType Type = (EEquipType)i;

		UEquipmentItem* Equipment = InPlayer->Equipment->GetEquipment(Type);
		if (Equipment)
		{
			Data->Equipment[i].EquipmentID = Equipment->GetItemID();
			Data->Equipment[i].EquipType = i;
		}
		else
			Data->Equipment[i].EquipmentID = CommonConst::EMPTY_ITEM_ID;
	}

	// QuickSlot
	Cnt = InPlayer->QuickSlot->Slots.Num();
	for (int32 i = 0; i < Cnt; ++i) 
	{
		if (InPlayer->QuickSlot->Slots[i])
			Data->QuickSlot[i] = InPlayer->QuickSlot->Slots[i]->GetIndex();
		else
			Data->QuickSlot[i] = -1;
	}

	// Save
	UGameplayStatics::AsyncSaveGameToSlot(Data, Data->PlayerID, Data->UserIndex);
}

void UPlayerDataManager::LoadData(const FString& InSlotName, FOnDataLoadCompleted&& Callback)
{
	// 데이터 불러오기
	UGameplayStatics::AsyncLoadGameFromSlot(
		InSlotName,
		0,
		FAsyncLoadGameFromSlotDelegate::CreateLambda(
			[this, Callback](const FString& SlotName, const int32 Index, USaveGame* SaveGame)
			{
				Data = Cast<UTDRPGSaveGame>(SaveGame);
				GetGameInstance()->GetSubsystem<UPlayerManager>()->SetPlayerData(Data);

				Callback.ExecuteIfBound();
			})
	);
}
