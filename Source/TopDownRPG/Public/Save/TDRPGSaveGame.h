// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDRPGConst.h"
#include "GameFramework/SaveGame.h"
#include "TDRPGSaveGame.generated.h"


USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FEquipmentSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString EquipmentID;

	UPROPERTY()
	int32 EquipType;

	FEquipmentSaveData() : EquipmentID(FTDRPGConst::EMPTY_ID), EquipType(-1)
	{}
};

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FInventorySaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString ItemID;

	UPROPERTY()
	int32 ItemType;

	UPROPERTY()
	int32 Quantity;

	FInventorySaveData() : ItemID(FTDRPGConst::EMPTY_ID), ItemType(-1), Quantity(0)
	{}
};

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FSkillSetSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SkillID;

	UPROPERTY()
	int32 InputKey;

	FSkillSetSaveData() : SkillID(FTDRPGConst::EMPTY_ID), InputKey(-1)
	{}
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
	FString CharID;

	UPROPERTY()
	uint32 CharLv;

	UPROPERTY()
	uint32 CharExp;

	// 재화 정보
	UPROPERTY()
	uint32 Gold;

	// 인벤토리 정보
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
	TArray<FInventorySaveData> Inventory;

	// 장비창 정보
	// EquipType => Index
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame")
	TArray<FEquipmentSaveData> Equipment;

	// 퀵슬롯 정보
	UPROPERTY()
	TArray<int32> QuickSlot;

	// 스킬셋 정보
	UPROPERTY()
	TArray<FSkillSetSaveData> SkillSet;
};