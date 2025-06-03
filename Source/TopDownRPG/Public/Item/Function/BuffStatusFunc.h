// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Function/ItemFuncBase.h"
#include "BuffStatusFunc.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBuffStatusFunc : public UItemFuncBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EStatus TargetStatus;
};
