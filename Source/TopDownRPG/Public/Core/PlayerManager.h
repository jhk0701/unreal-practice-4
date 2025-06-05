// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Character/Status.h"
#include "Property/Currency.h"
#include "PlayerManager.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY()
	FString PlayerID;
	
	UPROPERTY()
	FString CharID;

	UPROPERTY()
	uint32 CharLv;

	UPROPERTY()
	uint32 CharExp;

	UPROPERTY()
	uint32 Gold;
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	// 레벨
	UPROPERTY()
	uint32 Lv;
	// 경험치
	TUniquePtr<Status> Exp;
	// 골드
	TUniquePtr<Currency> CurrencyGold;

	TUniquePtr<FPlayerData> PlayerData;

	// 인벤토리
	// 소비, 재료 아이템 : ID, 갯수
	// 장비 아이템 : ID, 특수 옵션들
	TArray<class UItemBase> Inventory;

public:
	
	void LoadData();
	void SaveData();

	// 레벨 관리
	inline void AddExp(uint32 Value) { Exp->Add(Value); }
	void CheckExp(uint32 Max, uint32 Current);
	void LevelUp();

};
