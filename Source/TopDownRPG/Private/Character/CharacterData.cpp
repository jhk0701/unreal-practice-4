// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterData.h"
#include "Character/Status.h"
#include "Data/CharacterDataRow.h"
#include "Data/LevelingDataRow.h"
#include "Core/GameDataManager.h"

#include "TopDownRPG/TopDownRPG.h"

UCharacterData::UCharacterData()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterData::Initialize(uint32 InLv, uint32 InExp, FCharacterDataRow* InData)
{
	// TODO: 플레이어 데이터로부터 CharID 받아오기

	bIsDead = false;

	Lv = InLv;

	// 초기 데이터
	uint32	hp = InData->Hp,	mp = InData->Mp,	exp = 100;
	int32	str = InData->Str,	dex = InData->Dex,	intel = InData->Int;

	// 레벨링 반영
	TArray<int32> leveling;

	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	GameData->GetLeveling(CharID, Lv, leveling);

	for (int32 i = 0; i < leveling.Num(); ++i)
	{
		FString key = GameData->GetLevelingKey(CharID, i);
		FLevelingDataRow* row = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, FName(key));

		exp += row->ExpDemand * leveling[i];

		hp += row->Hp * leveling[i];
		mp += row->Mp * leveling[i];

		str += row->Str * leveling[i];
		dex += row->Dex * leveling[i];
		intel += row->Int * leveling[i];
	}

	// 스탯 반영
	Exp = MakeUnique<Status>(exp, InExp);

	Stat.Add(EStatus::Hp, MakeUnique<Status>(hp));
	Stat.Add(EStatus::Mp, MakeUnique<Status>(mp));

	Ability.Add(EAbility::Str, str);
	Ability.Add(EAbility::Dex, dex);
	Ability.Add(EAbility::Int, intel);

	// TODO : 스킬 반영

	Exp->OnValueChanged.AddUObject(this, &UCharacterData::CheckExp);
	Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UCharacterData::CheckIsDead);

	// Debugging();
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

void UCharacterData::CheckIsDead(uint32 Max, uint32 Current)
{
	if (bIsDead)
		return;

	PRINT_LOG(TEXT("Check player is dead :: %u / %u"), Current, Max);

	if (Current <= 0)
	{
		bIsDead = true;
		OnCharacterDead.Broadcast();
	}
}

uint32 UCharacterData::GetAttackPower()
{
	return Ability[EAbility::Str]; // uint32(100);
}

uint32 UCharacterData::GetDefensePower()
{
	return uint32(100);
}

void UCharacterData::Debugging()
{
	PRINT_LOG(TEXT("HP : %u"), Stat[EStatus::Hp]->GetMaxValue());
	PRINT_LOG(TEXT("MP : %u"), Stat[EStatus::Mp]->GetMaxValue());
	PRINT_LOG(TEXT("EXP : %u"), Exp->GetMaxValue());

	PRINT_LOG(TEXT("STR : %d"), Ability[EAbility::Str]);
	PRINT_LOG(TEXT("Dex : %d"), Ability[EAbility::Dex]);
	PRINT_LOG(TEXT("Int : %d"), Ability[EAbility::Int]);
}
