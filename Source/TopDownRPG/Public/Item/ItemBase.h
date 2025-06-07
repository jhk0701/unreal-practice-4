// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

struct FItemDataRow;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemUpdated, UItemBase*);

// 아이템의 경우 추상클래스로 선언
// 추상클래스로 선언하기 위해 Abstract 특정자 사용
UCLASS(Abstract)
class TOPDOWNRPG_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	FOnItemUpdated OnItemUpdated;
	
	// 아이템 데이터 주입
	virtual void Initialize(FItemDataRow* InData, FName* InID);
	virtual void Initialize(FItemDataRow* InData, FName* InID, uint32 InAmount);
	virtual bool TryAddItem(uint32 InAmount, uint32& OutRest);

protected:
	FName* ItemID = nullptr;
	FItemDataRow* Data = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	uint32 Quantity;
};
