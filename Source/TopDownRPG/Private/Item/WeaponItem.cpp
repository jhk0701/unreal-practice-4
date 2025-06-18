// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"
#include "TDRPGEnum.h"

#include "Data/WeaponDataRow.h"

ETableType UWeaponItem::GetItemType()
{
    return ETableType::Weapon;
}

EAbility UWeaponItem::GetDamageBase()
{
    FWeaponDataRow* Data = static_cast<FWeaponDataRow*>(GetData());
    return Data->DamageBase;
}
