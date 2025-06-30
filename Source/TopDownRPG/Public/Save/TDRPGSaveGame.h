// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save/InventorySaveData.h"
#include "Save/EquipmentSaveData.h"
#include "TDRPGSaveGame.generated.h"


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

	// 큇슬롯 정보
	UPROPERTY()
	TArray<int32> QuickSlot;
};