// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDRPGEnum.h"
#include "ItemFuncBase.generated.h"


USTRUCT()
struct FFunctionContext
{
	GENERATED_BODY()

	UItemFuncBase* Func;
	uint32 Value;
	float Duration;

	bool bOperateOneTime;
	float IntervalSec;
	float CurrentSec;

	FFunctionContext() {};
	FFunctionContext(UItemFuncBase* InFunc, uint32 InValue, float InDuration) :
		Func(InFunc),
		Value(InValue),
		Duration(InDuration),
		bOperateOneTime(FMath::IsNearlyZero(InDuration) ? true : false),
		IntervalSec(1.0f),
		CurrentSec(0.0f)
	{
	};
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UItemFuncBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void Operate(AActor* Object, uint32 Value);
	inline virtual uint32 Operate(uint32 Object, uint32 Value) { return 0; };
	inline FFunctionContext GetContext(uint32 Value, float Duration)
	{ 
		return FFunctionContext(this, Value, Duration);
	};
};
