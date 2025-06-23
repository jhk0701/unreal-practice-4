// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TDRPGSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FInventorySaveData
{
	GENERATED_BODY()

	FString ItemID;
	int32 Quantity;

	FInventorySaveData() : ItemID(TEXT("0")), Quantity(0) {};
};

USTRUCT(BlueprintType)
struct FEquipmentSaveData
{
	GENERATED_BODY()

	FString EquipmentID;
	int32 EquipType;

	FEquipmentSaveData() : EquipmentID(TEXT("0")), EquipType(-1) {};
};


UCLASS()
class TOPDOWNRPG_API UTDRPGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString PlayerID;

	UPROPERTY()
	FName PlayerName;
	
	UPROPERTY()
	int32 UserIndex;


	UPROPERTY()
	FString ClassID;

	UPROPERTY()
	uint32 CharLv;

	UPROPERTY()
	uint32 CharExp;

	// 재화 정보
	UPROPERTY()
	uint32 Gold;

	// 인벤토리 정보
	UPROPERTY(SaveGame)
	TArray<FInventorySaveData> Inventory;

	// 장비창 정보
	// EquipType => Index
	UPROPERTY(SaveGame)
	TArray<FEquipmentSaveData> Equipment;

	// 큇슬롯 정보
	UPROPERTY()
	TArray<int32> QuickSlot;
};

// 0. 새 게임 기능
// 1. 기존에 더미 데이터 대체
// 2. 데이터 세이브
// 3. 로드 기능 활성화
