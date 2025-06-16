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
	EOperateType OperType;
	
	UPROPERTY(EditAnywhere)
	EStatus TargetStatus;

	virtual uint32 Operate(uint32 Object, uint32 Value) override;

	// Inherited via UItemFuncBase
	void Operate(AActor* Object, uint32 Value) override;
};
