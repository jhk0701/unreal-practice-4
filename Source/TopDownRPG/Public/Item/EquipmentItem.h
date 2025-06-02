// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "EquipmentItem.generated.h"

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Weapon,

	Head,
	Top,
	Bottom,
	Glove,
	Shoes,
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UEquipmentItem : public UItemBase
{
	GENERATED_BODY()
	
public:
	void Equip();
	void Unequip();
};
