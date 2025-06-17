// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"
#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/ItemDataRow.h"

ETableType UWeaponItem::GetItemType()
{
    return ETableType::Weapon;
}
