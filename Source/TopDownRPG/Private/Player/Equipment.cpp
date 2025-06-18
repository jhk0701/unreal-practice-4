// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Equipment.h"
#include "TDRPGEnum.h"

#include "Item/EquipmentItem.h"
#include "Data/EquipmentDataRow.h"

UEquipment::UEquipment()
{
	// 초기화
	uint8 Cnt = (uint8)EEquipType::COUNT;
	for (uint8 i = 0; i < Cnt; ++i)
		Equipment.Add((EEquipType)i, nullptr);

	Cnt = (uint8)EStatus::COUNT;
	for (uint8 i = 0; i < Cnt; ++i)
		AddictiveStatus.Add((EStatus)i, 0);

	Cnt = (uint8)EAbility::COUNT;
	for (uint8 i = 0; i < Cnt; ++i)
		AddictiveAbility.Add((EAbility)i, 0);
}

void UEquipment::Equip(EEquipType InType, UEquipmentItem* InItem)
{
	// 이미 해당 부위가 장착중이라면 장착 해제 처리
	if (Equipment[InType])
		Unequip(InType);

	// 장비 장착
	Equipment[InType] = InItem;
	ApplyEquipment(InType);

	// 변경 사항 이벤트 알림
	OnEquipmentUpdated.Broadcast(InType);
}

void UEquipment::Unequip(EEquipType InType)
{
	UnapplyEquipment(InType);
	Equipment[InType] = nullptr;

	OnEquipmentUpdated.Broadcast(InType);
}

void UEquipment::ApplyEquipment(EEquipType InType)
{
	FEquipmentDataRow* Data = static_cast<FEquipmentDataRow*>(Equipment[InType]->GetData());
	
	AddictiveAttack += Data->AttackPower;
	AddictiveDefense += Data->DefensePower;

	for (auto& Pair : Data->Ability) 
		AddictiveAbility[Pair.Key] += Pair.Value;

	for (auto& Pair : Data->Status)
		AddictiveStatus[Pair.Key] += Pair.Value;
}

void UEquipment::UnapplyEquipment(EEquipType InType)
{
	FEquipmentDataRow* Data = static_cast<FEquipmentDataRow*>(Equipment[InType]->GetData());

	AddictiveAttack -= Data->AttackPower;
	AddictiveDefense -= Data->DefensePower;

	for (auto& Pair : Data->Ability)
		AddictiveAbility[Pair.Key] -= Pair.Value;

	for (auto& Pair : Data->Status)
		AddictiveStatus[Pair.Key] -= Pair.Value;
}
