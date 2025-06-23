// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerDataManager.generated.h"

class UTDRPGSaveGame;
class UPlayerManager;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UTDRPGSaveGame> Data;

private:
	TArray<FString> PlayerDataDir;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void CreateData(const FString& InPlayerName, const FString& InClassID);
	
	void SaveData(const UPlayerManager* InPlayer);

	void LoadData(const FString& InSlotName, const int32 InIndex);

private:
	void GetPlayerDatas(TArray<FString>& OutDirectories);

};
