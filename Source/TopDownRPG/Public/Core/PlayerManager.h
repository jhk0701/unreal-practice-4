// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Core/TDRPGSaveGame.h"
#include "Character/Status.h"
#include "Property/Currency.h"
#include "PlayerManager.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UTDRPGSaveGame> PlayerData;

	// 레벨
	UPROPERTY()
	uint32 Lv;

	UPROPERTY()
	FName ClassName;

	// 경험치
	TUniquePtr<FStatus> Exp;
	
	// 골드
	TUniquePtr<FCurrency> CurrencyGold;
	
	// 인벤토리
	UPROPERTY()
	TObjectPtr<class UInventory> Inventory;
	
	// 퀵슬롯
	UPROPERTY()
	TObjectPtr<class UQuickSlot> QuickSlot;

	// 장비창
	UPROPERTY()
	TObjectPtr<class UEquipment> Equipment;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void InitManager();

	void SetPlayerData(UTDRPGSaveGame* InPlayerData);

	inline FString GetClassID() const { return PlayerData->ClassID; }

	// 레벨 관리
	void AddExp(uint32 Value);
	void CheckExp(uint32 Max, uint32 Current);
	void LevelUp();

	void AddGold(uint32 Value);
};
