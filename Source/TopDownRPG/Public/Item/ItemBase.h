// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataModel.h"
#include "ItemBase.generated.h"

struct FItemDataRow;

enum class ETableType: uint8;
enum class ERarity: uint8;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemUpdated, UDataModel*);


UCLASS()
class TOPDOWNRPG_API UItemBase : public UDataModel
{
	GENERATED_BODY()

public:
	uint8 InventoryIndex = 0;
	uint32 Quantity;

	FOnItemUpdated OnItemUpdated;

	// 아이템 데이터 주입
	virtual void Initialize(const FString& InID, UGameDataManager* InDB) override;
	virtual void Initialize(const FString& InID, UGameDataManager* InDB, uint32 InAmount);

	virtual bool TryAddItem(uint32 InAmount, uint32& OutRest);

	virtual FItemDataRow* GetData();

	virtual ETableType GetItemType();

};
