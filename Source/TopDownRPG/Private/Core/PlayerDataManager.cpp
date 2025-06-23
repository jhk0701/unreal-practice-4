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
	IFileManager::Get().FindFiles(OutDirectories, *SaveFilePath, true, false);
}

void UPlayerDataManager::CreateData(const FString& InPlayerName, const FString& InClassID)
{
	// 초기 데이터 생성
	Data = Cast<UTDRPGSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDRPGSaveGame::StaticClass()));

	Data->PlayerName = FName(InPlayerName);
	Data->ClassID = InClassID;
	Data->UserIndex = 0;
	Data->PlayerID = InPlayerName + "_" + FDateTime::Now().ToString();

	Data->CharLv = 1;
	Data->CharExp = 0;
	Data->Gold = uint32(1000);

	GetGameInstance()->GetSubsystem<UPlayerManager>()->SetPlayerData(Data);

	// 초기 세이브
	UGameplayStatics::AsyncSaveGameToSlot(Data, Data->PlayerID, Data->UserIndex);
}

void UPlayerDataManager::SaveData(const UPlayerManager* InPlayer)
{
	Data->CharLv = InPlayer->Lv;
	Data->CharExp = InPlayer->Exp->GetCurrentValue();

	Data->Gold = InPlayer->CurrencyGold->GetCurrency();
	
	Data->Inventory.Init(FInventorySaveData(), UInventory::MAX_SIZE);
	Data->Equipment.Init(FEquipmentSaveData(), (int32)EEquipType::COUNT);
	Data->QuickSlot.Init(-1, UQuickSlot::MAX_SIZE);

	// Save
	UGameplayStatics::AsyncSaveGameToSlot(Data, Data->PlayerID, Data->UserIndex);
}

void UPlayerDataManager::LoadData(const FString& InSlotName, const int32 InIndex)
{
	// 데이터 불러오기
	UGameplayStatics::AsyncLoadGameFromSlot(
		InSlotName,
		InIndex,
		FAsyncLoadGameFromSlotDelegate::CreateLambda([&](const FString& SlotName, const int32 Index, USaveGame* SaveGame)
			{
				Data = Cast<UTDRPGSaveGame>(SaveGame);
				GetGameInstance()->GetSubsystem<UPlayerManager>()->SetPlayerData(Data);
			})
	);
}
