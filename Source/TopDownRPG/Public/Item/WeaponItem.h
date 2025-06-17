// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EquipmentItem.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UWeaponItem : public UEquipmentItem
{
	GENERATED_BODY()
	
public:
	virtual FItemDataRow* GetData() override;
};
