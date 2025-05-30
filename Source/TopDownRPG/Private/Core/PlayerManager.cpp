// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerManager.h"

void UPlayerManager::LoadData()
{
	// TODO : 데이터 불러오기
	PlayerData = 
	{
		// PlayerID
		TEXT("1"),

		// Character 정보
		TEXT("1001"),
		5,
		0,

		// 재화 : 골드
		uint32(100)
	};

	CurrencyGold = MakeUnique<Currency>(PlayerData.Gold);
}

void UPlayerManager::SaveData()
{
}
