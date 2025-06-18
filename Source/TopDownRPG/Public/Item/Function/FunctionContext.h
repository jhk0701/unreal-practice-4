// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FunctionContext.generated.h"

class UItemFuncBase;

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FFunctionContext
{
	GENERATED_BODY()

public:
	FFunctionContext() {}
	FFunctionContext(UItemFuncBase* InFunc, uint32 InValue, float InDuration) :
		Func(InFunc),
		Value(InValue),
		Duration(InDuration),
		bOperateOneTime(FMath::IsNearlyZero(Duration) ? true : false),
		IntervalSec(1.0f),
		CurrentSec(0.0f)
	{
	};

	UItemFuncBase* Func;
	uint32 Value;
	float Duration;

	bool bOperateOneTime;
	float IntervalSec;
	float CurrentSec;

};
