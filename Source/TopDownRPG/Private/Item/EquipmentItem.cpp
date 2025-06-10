// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquipmentItem.h"

#include "Core/GameDataManager.h"
#include "Data/EquipmentDataRow.h"

FItemDataRow* UEquipmentItem::GetData()
{
    UGameDataManager* GameData = GameInst->GetSubsystem<UGameDataManager>();
    return GameData->GetRow<FItemDataRow>(ETableType::Equipment, ItemID);
}

void UEquipmentItem::Equip()
{
}

void UEquipmentItem::Unequip()
{
}
