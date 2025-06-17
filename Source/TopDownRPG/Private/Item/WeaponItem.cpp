// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"
#include "Core/GameDataManager.h"
#include "Data/ItemDataRow.h"

FItemDataRow* UWeaponItem::GetData()
{
    UGameDataManager* GameData = GameInst->GetSubsystem<UGameDataManager>();
    return GameData->GetRow<FItemDataRow>(ETableType::Weapon, ItemID);
}
