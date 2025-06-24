// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "ItemDataRow.generated.h"

enum class ERarity : uint8;

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FItemDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ItemName;

	// 희귀도
	UPROPERTY(EditAnywhere)
	ERarity Rarity;

	UPROPERTY(EditAnywhere)
	uint32 NumOfDuplicate;

	// 기본 가격
	UPROPERTY(EditAnywhere)
	uint32 Price;

	// 구성요소
	UPROPERTY(EditAnywhere)
	FSoftObjectPath Thumbnail;

	// UPROPERTY(EditAnywhere)
	// FSoftObjectPath Mesh;
};
