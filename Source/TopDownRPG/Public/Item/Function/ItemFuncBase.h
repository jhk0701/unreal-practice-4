// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDRPGEnum.h"
#include "ItemFuncBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API UItemFuncBase : public UDataAsset
{
	GENERATED_BODY()

public:
	inline virtual void Activate(AActor* InTarget, uint32 InValue) {};
	inline virtual void Deactivate(AActor* InTarget, uint32 InValue) {};
};
