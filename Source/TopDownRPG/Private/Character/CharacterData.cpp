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

	ApplyData(InLv, InData);	// 데이터 반영
	ApplyEquipment(InEquipment);	// 장비 의존성 주입

	Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UCharacterData::CheckIsDead);
	Shield = MakeUnique<FStatus>(0);

	// TODO : 스킬 반영
}

void UCharacterData::ApplyData(uint32 InLv, FCharacterDataRow& InData)
{
	// 초기 데이터
	TMap<EStatus, int32> DataStatus = InData.Status;
	TMap<EAbility, int32> DataAbility = InData.Ability;

	// 레벨링 반영
	TArray<int32> Leveling;
	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	GameData->GetLeveling(ClassID, InLv, Leveling);

	for (int32 i = 0; i < Leveling.Num(); ++i)
	{
		FString Key = GameData->GetLevelingKey(ClassID, i);
		FLevelingDataRow* Row = GameData->GetRow<FLevelingDataRow>(ETableType::Leveling, Key);

		for (const auto& Pair : DataStatus) 
		{
			if (Row->Status.Contains(Pair.Key))
				DataStatus[Pair.Key] += Row->Status[Pair.Key] * Leveling[i];
		}

		for (const auto& Pair : DataAbility) 
		{
			if (Row->Ability.Contains(Pair.Key))
				DataAbility[Pair.Key] += Row->Ability[Pair.Key] * Leveling[i];
		}
	}

	for (const auto& Pair : DataStatus)
		BaseStatus.Add(Pair.Key, Pair.Value);
	
	for (const auto& Pair : DataAbility)
		BaseAbility.Add(Pair.Key, Pair.Value);

	// Stat 초기화
	uint8 Cnt = (uint8)EStatus::COUNT;
	for (uint8 i = 0; i < Cnt; ++i) 
	{
		EStatus Type = (EStatus)i;
		Stat.Add(Type, MakeUnique<FStatus>(BaseStatus[Type]));
	}
	
}

void UCharacterData::ApplyEquipment(UEquipment* InEquipment)
{
	if (!InEquipment)
		return;

	Equipment = InEquipment;
	
	UpdateEquipment(EEquipType::COUNT);

	Equipment->OnEquipmentUpdated.AddUObject(this, &UCharacterData::UpdateEquipment);
}

void UCharacterData::UpdateEquipment(EEquipType InType)
{
	uint8 Cnt = (uint8)EStatus::COUNT;
	for (uint8 i = 0; i < Cnt; ++i)
	{
		EStatus Type = (EStatus)i;

		if (!EquipmentStatus.Contains(Type))
			EquipmentStatus.Add(Type, 0);

		EquipmentStatus[Type] = Equipment->GetAddictiveStatus(Type);

		// Stat 업데이트
		uint32 CurVal = Stat[Type]->GetCurrentValue();
		uint32 NewVal = BaseStatus[Type] + EquipmentStatus[Type];
		NewVal < CurVal ? Stat[Type]->ChangeMaxValue(NewVal, NewVal) : Stat[Type]->ChangeMaxValue(NewVal);
	}

	Cnt = (uint8)EAbility::COUNT;
	for (uint8 i = 0; i < Cnt; ++i)
	{
		EAbility Type = (EAbility)i;

		if (!EquipmentAbility.Contains(Type))
			EquipmentAbility.Add(Type, 0);

		EquipmentAbility[Type] = Equipment->GetAddictiveAbility(Type);
	}
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

void UCharacterData::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 종료 시, 구독 해제
	if (Equipment) 
		Equipment->OnEquipmentUpdated.RemoveAll(this);
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
	// 최종 공격력 계산
	uint32 AdjustVal = 3; // TODO : 보정치 매직 넘버 제거 필요
	uint32 Result = 0;

	if (Equipment)
	{
		// 1. 공격력
		Result += Equipment->GetAddictiveAttack();

		// 2. 무기에 따른 스탯 반영
		UEquipmentItem* Equip = Equipment->GetEquipment(EEquipType::Weapon);
		if (Equip)
		{
			UWeaponItem* Weapon = Cast<UWeaponItem>(Equip);
			EAbility DamageBase = Weapon->GetDamageBase();

			Result += (BaseAbility[DamageBase] + EquipmentAbility[DamageBase]) / AdjustVal;
		}
	}
	else
	{
		Result = BaseAbility[EAbility::Str] / AdjustVal;
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
