// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Inventory.h"

#include "Kismet/GameplayStatics.h"
#include "Core/GameDataManager.h"

#include "Data/ConsumeDataRow.h"
#include "Item/ConsumeItem.h"

void UInventory::Initialize()
{
	Items.Init(nullptr, MaxSize);
}

void UInventory::AddItem(UItemBase& Item)
{
	// 빈공간 찾기
	uint8 Idx = GetBlankSpace();

	if (Idx >= 0)
		Items[Idx] = &Item;

	// TODO : 기능 고도화
	
	// 중복 체크
	// 중복 시, 새로운 인덱스에 할당
}

int16 UInventory::GetBlankSpace()
{
	for(int8 i = 0; i < MaxSize; ++i)
	{
		if (!Items[i])
			return i;
	}

	return -1;
}
