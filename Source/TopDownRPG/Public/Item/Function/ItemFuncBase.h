// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDRPGEnum.h"
#include "ItemFuncBase.generated.h"


struct FFunctionContext
{
	UItemFuncBase* Func;
	uint32 Value;
	float Duration;
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
	FFunctionContext& GetContext(uint32 Value, float Duration);
};
