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
	FString ItemID;
	int32 ItemType;
	int32 Quantity;

	FInventorySaveData();

};
