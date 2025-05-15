// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PlayerStatus.h"
#include "Character/Status.h"
#include "TopDownRPG/TopDownRPG.h"

UPlayerStatus::UPlayerStatus()
{
}

void UPlayerStatus::InitLvAndExp(uint32 InitLv, uint32 InitExp)
{
	Lv = InitLv;
	Exp = MakeUnique<Status>(InitExp, (uint32)0);

	Exp->OnValueChanged.AddUObject(this, &UPlayerStatus::CheckExp);
}

void UPlayerStatus::CheckExp(uint32 Max, uint32 Current)
{
	if (Current >= Max)
		LevelUp();
}

void UPlayerStatus::LevelUp()
{
	++Lv;
	Exp->ChangeMaxValue(Exp->GetMaxValue() * 2); // TODO : 레벨 관련 데이터 테이블 작성
}


void UPlayerStatus::InitStatus(const TArray<EStatus>& StatusType, const TArray<uint32>& InitVal)
{
	if (StatusType.Num() != InitVal.Num())
		return;

	bIsDead = false;

	for (int32 i = 0; i < StatusType.Num(); ++i)
		Stat.Add(StatusType[i], MakeUnique<Status>(InitVal[i]));

	Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UPlayerStatus::CheckPlayerIsDead);
}

void UPlayerStatus::CheckPlayerIsDead(uint32 Max, uint32 Current)
{
	if (bIsDead) return;

	if (Current <= 0)
	{
		bIsDead = true;
		OnPlayerDead();
	}
}

void UPlayerStatus::OnPlayerDead()
{
	PRINT_LOG(TEXT("Player is dead"));
}
