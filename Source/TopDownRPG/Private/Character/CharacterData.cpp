// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterData.h"
#include "TDRPGEnum.h"

#include "Core/GameDataManager.h"
#include "Data/CharacterDataRow.h"
#include "Data/LevelingDataRow.h"

#include "Core/PlayerManager.h"
#include "Player/Equipment.h"

#include "Item/Function/ItemFuncBase.h"
#include "Item/EquipmentItem.h"
#include "Item/WeaponItem.h"

#include "TopDownRPG/TopDownRPG.h"

UCharacterData::UCharacterData()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterData::Initialize(uint32 InLv, FCharacterDataRow& InData, UEquipment* InEquipment)
{
	bIsDead = false;

	// 초기 데이터
	uint32	Hp = InData.Hp,	Mp = InData.Mp;
	int32	Str = InData.Str,	Dex = InData.Dex,	Int = InData.Int;
	
	// 장비 의존성 주입
	// nullptr일 수 있으니 유효성 주의
	Equipment = InEquipment;

	// 레벨링 반영
	TArray<int32> Leveling;
	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	GameData->GetLeveling(CharID, InLv, Leveling);

	for (int32 i = 0; i < Leveling.Num(); ++i)
	{
		FString key = GameData->GetLevelingKey(CharID, i);
		FLevelingDataRow* row = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, key);

		Hp += row->Hp * Leveling[i];
		Mp += row->Mp * Leveling[i];

		Str += row->Str * Leveling[i];
		Dex += row->Dex * Leveling[i];
		Int += row->Int * Leveling[i];
	}

	Stat.Add(EStatus::Hp, MakeUnique<Status>(Hp));
	Stat.Add(EStatus::Mp, MakeUnique<Status>(Mp));
	Stat.Add(EStatus::Shield, MakeUnique<Status>(0));

	Ability.Add(EAbility::Str, Str);
	Ability.Add(EAbility::Dex, Dex);
	Ability.Add(EAbility::Int, Int);

	Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UCharacterData::CheckIsDead);
	// TODO : 스킬 반영

	// Debugging();
}

void UCharacterData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 기한 만료된 버프 해제
	while (!BuffReleaseQueue.IsEmpty())
	{
		FString Key;
		BuffReleaseQueue.Dequeue(Key);
		BuffFunc.Remove(Key);
	}

	for (auto& Pair : BuffFunc)
	{
		// 버프 기한 체크
		Pair.Value.Duration -= DeltaTime;

		if (Pair.Value.Duration < 0)
			BuffReleaseQueue.Enqueue(Pair.Key); // 다음 틱에 버프 해제
	}
}

void UCharacterData::CheckIsDead(uint32 Max, uint32 Current)
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
	// TODO : 최종 공격력 계산
	uint32 Result = 0;

	if (Equipment)
	{
		// 1. 추가 공격력
		Result += Equipment->GetAddictiveAttack();

		// 2. 무기에 따른 스탯 반영
		UEquipmentItem* Equip = Equipment->GetEquipment(EEquipType::Weapon);
		if (Equip)
		{
			UWeaponItem* Weapon = Cast<UWeaponItem>(Equip);
			EAbility DamageBase = Weapon->GetDamageBase();

			// TODO : 보정치 매직 넘버 제거 필요
			Result += Ability[DamageBase] / 3;
		}
	}
	
	// TODO : 버프 반영

	return Result;
}

uint32 UCharacterData::GetDefensePower()
{
	uint32 Result = 0;

	if (Equipment)
		Result += Equipment->GetAddictiveDefense();

	return Result;
}

void UCharacterData::AddBuff(FString& InItemID, FFunctionContext InContext)
{
	// 버프 중복 사용 시, 시간 추가
	if (BuffFunc.Contains(InItemID))
		BuffFunc[InItemID].Duration += InContext.Duration;
	else
		BuffFunc.Add(InItemID, InContext);
}

void UCharacterData::Debugging()
{
	PRINT_LOG(TEXT("HP : %u"), Stat[EStatus::Hp]->GetMaxValue());
	PRINT_LOG(TEXT("MP : %u"), Stat[EStatus::Mp]->GetMaxValue());

	PRINT_LOG(TEXT("STR : %d"), Ability[EAbility::Str]);
	PRINT_LOG(TEXT("Dex : %d"), Ability[EAbility::Dex]);
	PRINT_LOG(TEXT("Int : %d"), Ability[EAbility::Int]);
}
