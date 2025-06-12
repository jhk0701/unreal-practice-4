// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquipmentItem.h"

#include "Core/PlayerManager.h"
#include "Player/Equipment.h"

#include "Core/GameDataManager.h"
#include "Data/EquipmentDataRow.h"

#include "TopDownRPG/TopDownRPG.h"


FItemDataRow* UEquipmentItem::GetData()
{
    UGameDataManager* GameData = GameInst->GetSubsystem<UGameDataManager>();
    return GameData->GetRow<FItemDataRow>(ETableType::Equipment, ItemID);
}

void UEquipmentItem::Equip()
{
    UPlayerManager* PlayerManager = GameInst->GetSubsystem<UPlayerManager>();

    auto* BaseData = GetData();
    FEquipmentDataRow* Data = static_cast<FEquipmentDataRow*>(BaseData);

    PlayerManager->Equipment->Equip(Data->EquipType, this);

    PRINT_LOG(TEXT("Equip Item"));

    // 인벤토리에서 해당 아이템 제거
}

void UEquipmentItem::Unequip()
{
}
