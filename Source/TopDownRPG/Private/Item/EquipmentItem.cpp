// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquipmentItem.h"
#include "TDRPGEnum.h"

#include "Core/PlayerManager.h"
#include "Player/Inventory.h"
#include "Player/Equipment.h"

#include "Core/GameDataManager.h"
#include "Data/EquipmentDataRow.h"

void UEquipmentItem::Initialize(const FString& InID, UGameDataManager* InDB, uint32 InAmount)
{
    // 장비의 경우 무조건 갯수를 1로 고정
    Super::Initialize(InID, InDB, 1);
}

ETableType UEquipmentItem::GetItemType()
{
    return ETableType::Equipment;
}

void UEquipmentItem::Equip(UPlayerManager* InPlayer)
{
    FEquipmentDataRow* Data = static_cast<FEquipmentDataRow*>(GetData());

    // 장비창에 추가
    InPlayer->Equipment->Equip(Data->EquipType, this);

    // 인벤토리에서 제거
    InPlayer->Inventory->RemoveItem(InventoryIndex);
}

void UEquipmentItem::Unequip(UPlayerManager* InPlayer)
{
    FEquipmentDataRow* Data = static_cast<FEquipmentDataRow*>(GetData());

    // 장비창에서 제거
    InPlayer->Equipment->Unequip(Data->EquipType);

    // 인벤토리에 추가
    InPlayer->Inventory->AddItem(this);
}
