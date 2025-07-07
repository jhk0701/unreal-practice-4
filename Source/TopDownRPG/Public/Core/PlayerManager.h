// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Character/Status.h"
#include "Property/Currency.h"
#include "PlayerManager.generated.h"

class UTDRPGSaveGame;
class UInventory;
class UQuickSlot;
class UEquipment;
class USkillSlot;

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

	UPROPERTY()
	FName ClassName;

	// 레벨
	UPROPERTY()
	uint32 Lv;

	// 경험치
	TUniquePtr<FStatus> Exp;
	
	// 골드
	TUniquePtr<FCurrency> CurrencyGold;
	
	// 인벤토리
	UPROPERTY()
	TObjectPtr<UInventory> Inventory;
	
	// 퀵슬롯
	UPROPERTY()
	TObjectPtr<UQuickSlot> QuickSlot;

	// 장비창
	UPROPERTY()
	TObjectPtr<UEquipment> Equipment;

	// 스킬 슬롯
	UPROPERTY()
	TObjectPtr<USkillSlot> SkillSlot;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void InitManager();
	void SetPlayerData(UTDRPGSaveGame* InPlayerData);

	FName& GetPlayerName() const;
	FString& GetCharID() const;

	// 레벨 관리
	void AddExp(uint32 Value);
	void CheckExp(uint32 Max, uint32 Current);
	void LevelUp();

private:
	void InitLvAndExp(uint32 InLv, uint32 InExp);
	void InitGold(uint32 InGold);
	void InitInventory();
	void InitEquipment();
	void InitQuickSlot();
	
};
