// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentSaveData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FEquipmentSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString EquipmentID;
	UPROPERTY()
	int32 EquipType;

	FEquipmentSaveData();
};
