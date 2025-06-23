// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemBase.generated.h"

struct FItemDataRow;

enum class ETableType :uint8;
enum class ERarity :uint8;

DECLARE_ENUM_TO_STRING(ERarity);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemUpdated, UItemBase*);


UCLASS()
class TOPDOWNRPG_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	uint8 InventoryIndex = 0;
	uint32 Quantity;

	FOnItemUpdated OnItemUpdated;

protected:
	UPROPERTY()
	FString ItemID;

	// TODO : 개선 방법 없는지 생각해야함
	UPROPERTY()
	TObjectPtr<UGameInstance> GameInst;

public:
	// 아이템 데이터 주입
	virtual void Initialize(FString InID, UGameInstance* InGameInst);
	virtual void Initialize(FString InID, UGameInstance* InGameInst, uint32 InAmount);
	virtual bool TryAddItem(uint32 InAmount, uint32& OutRest);
	
	virtual FItemDataRow* GetData();
	virtual ETableType GetItemType();

	inline const FString& GetItemID() const { return ItemID; }

	FString EnumToString(const ERarity InValue) const;
};
