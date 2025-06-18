// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemFuncBase.generated.h"

enum class EOperateType : uint8;
enum class EStatus : uint8;
enum class EAbility : uint8;

struct FFunctionContext;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UItemFuncBase : public UDataAsset
{
	GENERATED_BODY()

public:
	inline virtual void Operate(AActor* Object, uint32 Value) {};
	inline virtual uint32 Operate(uint32 Object, uint32 Value) { return 0; };
	virtual FFunctionContext GetContext(uint32 Value, float Duration);
};
