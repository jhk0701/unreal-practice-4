// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

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
	TArray<class UItemBase*> Items;

	void Initialize();
	void AddItem(class UItemBase& Item);
};
