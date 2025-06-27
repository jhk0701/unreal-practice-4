// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySaveData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FInventorySaveData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString ItemID;
	UPROPERTY()
	int32 ItemType;
	UPROPERTY()
	int32 Quantity;

	FInventorySaveData();

};
