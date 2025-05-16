// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CharacterStatus.h"
#include "Character/Status.h"

#include "TopDownRPG/TopDownRPG.h" // 디버깅

UCharacterStatus::UCharacterStatus()
{
}

void UCharacterStatus::InitLvAndExp(uint32 InitLv, uint32 InitExp)
{
	Lv = InitLv;
	Exp = MakeUnique<Status>(InitExp, (uint32)0);

	Exp->OnValueChanged.AddUObject(this, &UCharacterStatus::CheckExp);
}

void UCharacterStatus::CheckExp(uint32 Max, uint32 Current)
{
	if (Current >= Max)
		LevelUp();
}

void UCharacterStatus::LevelUp()
{
	++Lv;
	Exp->ChangeMaxValue(Exp->GetMaxValue() * 2); // TODO : 레벨 관련 데이터 테이블 작성
}


void UCharacterStatus::InitStatus(const TArray<EStatus>& StatusType, const TArray<uint32>& InitVal)
{
	if (StatusType.Num() != InitVal.Num())
		return;

	bIsDead = false;

	for (int32 i = 0; i < StatusType.Num(); ++i)
		Stat.Add(StatusType[i], MakeUnique<Status>(InitVal[i]));

	Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UCharacterStatus::CheckPlayerIsDead);
}

void UCharacterStatus::CheckPlayerIsDead(uint32 Max, uint32 Current)
{
	if (bIsDead) return;

	if (Current <= 0)
	{
		bIsDead = true;
		OnPlayerDead();
	}
}

void UCharacterStatus::OnPlayerDead()
{
	PRINT_LOG(TEXT("Player is dead"));
}
