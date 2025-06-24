// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "TDRPGEnum.h"
#include "Data/InnerStringArray.h"
#include "MerchantDataRow.generated.h"


USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FMerchantDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName MerchantName;

	// 아이템 가격 할인 - 특수한 상황에서 사용
	UPROPERTY(EditAnywhere)
	int32 Discount;

	// 재구입 시, 아이템 가격 감가 수치
	UPROPERTY(EditAnywhere)
	int32 ResellCost;

	UPROPERTY(EditAnywhere)
	TMap<ETableType, FInnerStringArray> ProductID;

};
