// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

struct FItemDataRow;

// 아이템의 경우 추상클래스로 선언
// 추상클래스로 선언하기 위해 Abstract 특정자 사용
UCLASS(Abstract)
class TOPDOWNRPG_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	// 아이템 데이터 주입
	inline virtual void Initialize(FItemDataRow& InData) { Data = &InData; };
	virtual bool TryAddItem(uint8 InAmount, uint8& OutRest);

protected:
	FItemDataRow* Data = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	uint8 Quantity;
};
