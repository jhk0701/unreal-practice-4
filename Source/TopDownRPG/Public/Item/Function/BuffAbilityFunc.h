// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Function/ItemFuncBase.h"
#include "BuffAbilityFunc.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBuffAbilityFunc : public UItemFuncBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EAbility TargetAbility;
};
