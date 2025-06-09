// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ItemDataRow.h"
#include "ItemBase.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemUpdated, UItemBase*);


UCLASS()
class TOPDOWNRPG_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	// 아이템 데이터 주입
	virtual void Initialize(FItemDataRow* InData, FName* InID);
	virtual void Initialize(FItemDataRow* InData, FName* InID, uint32 InAmount);
	virtual bool TryAddItem(uint32 InAmount, uint32& OutRest);

	inline const uint32 GetQuantity() { return Quantity; }
	inline FItemDataRow* GetData() { return &Data; }
	
	FOnItemUpdated OnItemUpdated;

protected:
	FName* ItemID;
	FItemDataRow Data;

	UPROPERTY(VisibleAnywhere)
	uint32 Quantity;
};
