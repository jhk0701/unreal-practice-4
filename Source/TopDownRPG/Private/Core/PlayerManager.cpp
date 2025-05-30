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

	Lv = PlayerData.CharLv;
	
	// TODO : Exp 계산

	Exp = MakeUnique<Status>(200, PlayerData.CharExp);
	CurrencyGold = MakeUnique<Currency>(PlayerData.Gold);

	Exp->OnValueChanged.AddUObject(this, &UPlayerManager::CheckExp);
}

void UPlayerManager::SaveData()
{
	PlayerData.CharLv = Lv;
	PlayerData.CharExp = Exp->GetCurrentValue();

	PlayerData.Gold = CurrencyGold->GetCurrency();
	// TODO : Save
}

void UPlayerManager::CheckExp(uint32 Max, uint32 Current)
{
	if (Current >= Max)
		LevelUp();
}

void UPlayerManager::LevelUp()
{
	++Lv;
	Exp->ChangeMaxValue(Exp->GetMaxValue() * 2, 0); // TODO : 레벨 관련 데이터 테이블 작성

}
