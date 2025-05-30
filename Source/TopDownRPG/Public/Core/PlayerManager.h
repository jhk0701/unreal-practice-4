// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
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
	int32 CharLv;

	UPROPERTY()
	int32 CharExp;

	// TODO : 재화
	// TODO : 인벤토리
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	FPlayerData PlayerData;

public:
	inline const FPlayerData& GetPlayerData() { return PlayerData; }
	
	void LoadData();
	void SaveData();

};
