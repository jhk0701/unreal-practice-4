// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterData.h"
#include "Character/Status.h"
#include "Data/CharacterDataRow.h"


UCharacterData::UCharacterData()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterData::Initialize(uint32 InLv, uint32 InExp, FCharacterDataRow& InData)
{
	bIsDead = false;

	Lv = InLv;
	Exp = MakeUnique<Status>(InExp, (uint32)0);
	Exp->OnValueChanged.AddUObject(this, &UCharacterData::CheckExp);

	Stat.Add(EStatus::Hp, MakeUnique<Status>(InData.Hp));
	Stat.Add(EStatus::Mp, MakeUnique<Status>(InData.Mp));
	
	Ability.Add(EAbility::Str, InData.Str);
	Ability.Add(EAbility::Dex, InData.Dex);
	Ability.Add(EAbility::Int, InData.Int);

	// TODO : 스킬 반영

	Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UCharacterData::CheckPlayerIsDead);
}

void UCharacterData::CheckExp(uint32 Max, uint32 Current)
{
	if (Current >= Max)
		LevelUp();
}

void UCharacterData::LevelUp()
{
	++Lv;
	Exp->ChangeMaxValue(Exp->GetMaxValue() * 2); // TODO : 레벨 관련 데이터 테이블 작성
}

void UCharacterData::CheckPlayerIsDead(uint32 Max, uint32 Current)
{
	if (bIsDead)
		return;

	if (Current <= 0)
	{
		bIsDead = true;
		OnCharacterDead.Broadcast();
	}
}

uint32 UCharacterData::GetAttackPower()
{
	return uint32(100);
}

uint32 UCharacterData::GetDefensePower()
{
	return uint32(100);
}

