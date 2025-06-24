// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InnerStringArray.generated.h"

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FInnerStringArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Array;
};
