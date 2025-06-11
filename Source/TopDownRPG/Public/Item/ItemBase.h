// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TDRPGEnum.h"
#include "ItemBase.generated.h"

struct FItemDataRow;

DECLARE_ENUM_TO_STRING(ERarity);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemUpdated, UItemBase*);


UCLASS()
class TOPDOWNRPG_API UItemBase : public UObject
{
	GENERATED_BODY()

protected:
	FName ItemID;

	UPROPERTY(VisibleAnywhere)
	uint32 Quantity;

	// TODO : 개선 방법 없는지 생각해야함
	UPROPERTY(VisibleAnywhere)
	UGameInstance* GameInst;

public:
	// 아이템 데이터 주입
	virtual void Initialize(FName InID, UGameInstance* InGameInst);
	virtual void Initialize(FName InID, UGameInstance* InGameInst, uint32 InAmount);
	virtual bool TryAddItem(uint32 InAmount, uint32& OutRest);
	virtual FItemDataRow* GetData();

	inline const uint32 GetQuantity() { return Quantity; }

	FString EnumToString(const ERarity InValue);

	FOnItemUpdated OnItemUpdated;
};
