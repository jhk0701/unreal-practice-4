// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDRPGEnum.h"
#include "Equipment.generated.h"

class UEquipmentItem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipmentChanged, EEquipType);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UEquipment : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<EEquipType, UEquipmentItem*> Equipment;

	FOnEquipmentChanged OnEquipmentChanged;

public:
	UEquipment();

	// 장착, 장착 해제
	void Equip(EEquipType InType, UEquipmentItem* InItem);
	void Unequip(EEquipType InType);

};
