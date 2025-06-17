// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

class UItemBase;

// 이벤트 호출 시 변경된 Index 전달
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, uint8);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UInventory : public UObject
{
	GENERATED_BODY()
	
public:
	uint8 MaxSize = 80;

	// 소비, 재료 아이템 : ID, 갯수
	// 장비 아이템 : ID, 특수 옵션들
	UPROPERTY()
	TArray<UItemBase*> Items;

	FOnInventoryUpdated OnInventoryUpdated;

public:
	UInventory();

	bool AddItem(UItemBase* InItem);

	void RemoveItem(uint8 InIdx);

private:
	bool GetBlankSpace(uint8& OutIndex);

	// 쿼리 형태로 검색 조건을 받기
	// 유연하게 쿼리를 받기 위해서 TFunction 사용
	bool FindItem(UItemBase* InItem, uint8& OutIndex, TFunction<bool(UItemBase*)> InQuery = nullptr);

	bool AssignNewItem(UItemBase* InItem);
};
