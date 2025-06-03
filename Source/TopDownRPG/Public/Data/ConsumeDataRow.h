// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataRow.h"
#include "TDRPGEnum.h"
#include "ConsumeDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FConsumeDataRow : public FItemDataRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EConsumeType Type;

	// 효과 적용 시간 (초단위)
	// 1초 당 Value 값만큼 회복
	// 0초 : 즉시 회복
	UPROPERTY(EditAnywhere)
	uint8 Duration; 

	// 적용량
	UPROPERTY(EditAnywhere)
	uint32 Value;
};
