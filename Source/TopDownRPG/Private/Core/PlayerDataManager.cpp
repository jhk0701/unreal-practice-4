// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerDataManager.h"
#include "Core/PlayerManager.h"
#include "Core/TDRPGSaveGame.h"

#include "CommonConst.h"

#include "Character/Status.h"
#include "Property/Currency.h"

#include "Item/ItemBase.h"
#include "Item/ConsumeItem.h"
#include "Item/EquipmentItem.h"
#include "Item/WeaponItem.h"

#include <Kismet/GameplayStatics.h>

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

	//초기 세이브
	UGameplayStatics::AsyncSaveGameToSlot(Data, Data->PlayerID, Data->UserIndex);
}

void UPlayerDataManager::SaveData(const UPlayerManager* InPlayer)
{
	Data->CharLv = InPlayer->Lv;
	Data->CharExp = InPlayer->Exp->GetCurrentValue();

	Data->Gold = InPlayer->CurrencyGold->GetCurrency();

	// TODO : Save
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
			}));
}
