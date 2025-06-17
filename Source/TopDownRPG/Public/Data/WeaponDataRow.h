// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EquipmentDataRow.h"
#include "WeaponDataRow.generated.h"

enum class EAbility : uint8;

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FWeaponDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()

public:
	// 데미지 계산 시 사용할 스탯
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAbility DamageBase;
};
