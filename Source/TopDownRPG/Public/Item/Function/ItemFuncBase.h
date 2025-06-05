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

	FFunctionContext() {};
	FFunctionContext(UItemFuncBase* InFunc, uint32 InValue, float InDuration) : 
		Func(InFunc), 
		Value(InValue), 
		Duration(InDuration)
	{};
};

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API UItemFuncBase : public UDataAsset
{
	GENERATED_BODY()

public:
	inline virtual uint32 Operate(uint32 Object, uint32 Value) { return Value; };
	inline virtual void Operate(AActor* Object, uint32 Value) { };
	inline TSharedPtr<FFunctionContext> GetContext(uint32 Value, float Duration) 
	{ 
		return MakeShared<FFunctionContext>(this, Value, Duration); 
	};
};
