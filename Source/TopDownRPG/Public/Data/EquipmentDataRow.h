// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataRow.h"
#include "TDRPGEnum.h"
#include "EquipmentDataRow.generated.h"

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FEquipmentDataRow : public FItemDataRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EEquipType EquipType;

	// 아이템이 제공할 혜택
	UPROPERTY(EditAnywhere)
	uint32 AttackPower;
	UPROPERTY(EditAnywhere)
	uint32 DefensePower;

	// 추가 어빌리티
	UPROPERTY(EditAnywhere)
	TMap<EAbility, uint32> Ability;
	// 추가 스탯
	UPROPERTY(EditAnywhere)
	TMap<EStatus, uint32> Status;
};
