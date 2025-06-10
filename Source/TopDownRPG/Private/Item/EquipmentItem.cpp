// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquipmentItem.h"

#include "Core/GameDataManager.h"
#include "Data/EquipmentDataRow.h"

FItemDataRow* UEquipmentItem::GetData() const
{
    UGameDataManager* GameData = GameInst->GetSubsystem<UGameDataManager>();
    FItemDataRow* Data = GameData->GetRow<FItemDataRow>(ETableType::Equipment, *ItemID);

    if (Data)
        return Data;

    return nullptr;
}

void UEquipmentItem::Equip()
{
}

void UEquipmentItem::Unequip()
{
}
