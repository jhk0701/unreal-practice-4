// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TDRPGSaveGame.generated.h"


UCLASS()
class TOPDOWNRPG_API UTDRPGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName PlayerName;

	UPROPERTY()
	FString PlayerID;

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

	// 장비창 정보

	// 큇슬롯 정보
};

// 0. 새 게임 기능
// 1. 기존에 더미 데이터 대체
// 2. 데이터 세이브
// 3. 로드 기능 활성화
