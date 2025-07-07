// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ItemFactory.h"

#include "TDRPGEnum.h"
#include "Item/ItemBase.h"
#include "Item/ConsumeItem.h"
#include "Item/EquipmentItem.h"
#include "Item/WeaponItem.h"


UItemBase* UItemFactory::GetItem(ETableType ItemType, FString& InItemID, uint32 InQuantity)
{
	if (InItemID == FTDRPGConst::EMPTY_ITEM_ID)
		return nullptr;

	UItemBase* Result = nullptr;

	switch (ItemType)
	{
	case ETableType::Weapon:
		Result = GetItem<UWeaponItem>(InItemID, InQuantity);
		break;
	case ETableType::Equipment:
		Result = GetItem<UEquipmentItem>(InItemID, InQuantity);
		break;
	case ETableType::Consume:
		Result = GetItem<UConsumeItem>(InItemID, InQuantity);
		break;
	case ETableType::Ingredient:
		Result = GetItem<UItemBase>(InItemID, InQuantity);
		break;
	}

	return Result;
}
