// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquipmentItem.h"
#include "TDRPGEnum.h"

#include "Core/PlayerManager.h"
#include "Player/Inventory.h"
#include "Player/Equipment.h"

#include "Core/GameDataManager.h"
#include "Data/EquipmentDataRow.h"


void UEquipmentItem::Initialize(FString InID, UGameInstance* InGameInst, uint32 InAmount)
{
    // 장비의 경우 무조건 갯수를 1로 고정
    Super::Initialize(InID, InGameInst, 1);
}

ETableType UEquipmentItem::GetItemType()
{
    return ETableType::Equipment;
}

void UEquipmentItem::Equip()
{
    UPlayerManager* PlayerManager = GameInst->GetSubsystem<UPlayerManager>();
    FEquipmentDataRow* Data = static_cast<FEquipmentDataRow*>(GetData());

    // 장비창에 추가
    PlayerManager->Equipment->Equip(Data->EquipType, this);

    // 인벤토리에서 제거
    PlayerManager->Inventory->RemoveItem(InventoryIndex);
}

void UEquipmentItem::Unequip()
{
    UPlayerManager* PlayerManager = GameInst->GetSubsystem<UPlayerManager>();
    FEquipmentDataRow* Data = static_cast<FEquipmentDataRow*>(GetData());

    // 장비창에서 제거
    PlayerManager->Equipment->Unequip(Data->EquipType);

    // 인벤토리에 추가
    PlayerManager->Inventory->AddItem(this);
}
