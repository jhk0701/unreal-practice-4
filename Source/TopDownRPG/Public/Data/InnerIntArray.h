// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InnerIntArray.generated.h"

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FInnerIntArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> Array;
};
