// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Equipment.h"

#include "Item/EquipmentItem.h"

UEquipment::UEquipment()
{
	// 초기화
	uint8 Cnt = (uint8)EEquipType::COUNT;

	for (uint8 i = 0; i < Cnt; ++i) 
		Equipment.Add((EEquipType)i, nullptr);
}

void UEquipment::Equip(EEquipType InType, UEquipmentItem* InItem)
{
	// 장비 장착
	// 버프에 대한 것은 캐릭터 단에서 처리
	Equipment[InType] = InItem;

	// 변경 사항 이벤트 알림
	OnEquipmentChanged.Broadcast(InType);
}

void UEquipment::Unequip(EEquipType InType)
{
	Equipment[InType] = nullptr;

	OnEquipmentChanged.Broadcast(InType);
}
