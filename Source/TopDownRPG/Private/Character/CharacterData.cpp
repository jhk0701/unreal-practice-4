// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterData.h"
#include "Character/Status.h"

#include "Core/GameDataManager.h"
#include "Data/CharacterDataRow.h"
#include "Data/LevelingDataRow.h"

#include "TopDownRPG/TopDownRPG.h"

UCharacterData::UCharacterData()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterData::Initialize(uint32 InLv, FCharacterDataRow* InData)
{
	bIsDead = false;

	// 초기 데이터
	uint32	Hp = InData->Hp,	Mp = InData->Mp;
	int32	Str = InData->Str,	Dex = InData->Dex,	Int = InData->Int;

	// 레벨링 반영
	TArray<int32> Leveling;
	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	GameData->GetLeveling(CharID, InLv, Leveling);

	for (int32 i = 0; i < Leveling.Num(); ++i)
	{
		FString key = GameData->GetLevelingKey(CharID, i);
		FLevelingDataRow* row = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, FName(key));

		Hp += row->Hp * Leveling[i];
		Mp += row->Mp * Leveling[i];

		Str += row->Str * Leveling[i];
		Dex += row->Dex * Leveling[i];
		Int += row->Int * Leveling[i];
	}

	Stat.Add(EStatus::Hp, MakeUnique<Status>(Hp));
	Stat.Add(EStatus::Mp, MakeUnique<Status>(Mp));
	// Stat.Add(EStatus::Shield, MakeUnique<Status>(0));

	Ability.Add(EAbility::Str, Str);
	Ability.Add(EAbility::Dex, Dex);
	Ability.Add(EAbility::Int, Int);

	// TODO : 스킬 반영
	Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UCharacterData::CheckIsDead);

	// Debugging();
}

void UCharacterData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 기한 만료된 버프 해제
	if (BuffToBeReleased.Num() > 0)
	{
		for (auto& Key : BuffToBeReleased)
		{
			BuffFunc.Remove(Key);
		}

		BuffToBeReleased.Empty();
	}

	for (auto& Pair : BuffFunc)
	{
		Pair.Value->Duration -= DeltaTime;
		if (Pair.Value->Duration < 0)
			BuffToBeReleased.Add(Pair.Key); // 다음 틱에 버프 해제
	}
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
	// TODO : 최종 공격력 계산
	return Ability[EAbility::Str];
}

uint32 UCharacterData::GetDefensePower()
{
	// TODO : 최종 방어력 계산
	return uint32(100);
}

void UCharacterData::AddBuff(FName& InItemID, FFunctionContext& InContext)
{
	if(BuffFunc.Contains(InItemID))
		BuffFunc[InItemID]->Duration += InContext.Duration;
	else
		BuffFunc.Add(InItemID, &InContext);
}

void UCharacterData::Debugging()
{
	PRINT_LOG(TEXT("HP : %u"), Stat[EStatus::Hp]->GetMaxValue());
	PRINT_LOG(TEXT("MP : %u"), Stat[EStatus::Mp]->GetMaxValue());
	// PRINT_LOG(TEXT("EXP : %u"), Exp->GetMaxValue());

	PRINT_LOG(TEXT("STR : %d"), Ability[EAbility::Str]);
	PRINT_LOG(TEXT("Dex : %d"), Ability[EAbility::Dex]);
	PRINT_LOG(TEXT("Int : %d"), Ability[EAbility::Int]);
}
