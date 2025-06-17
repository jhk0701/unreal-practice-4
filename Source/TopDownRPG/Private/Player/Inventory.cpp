// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Inventory.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"

UInventory::UInventory()
{
	Items.Init(nullptr, MaxSize);
}

bool UInventory::AddItem(UItemBase* InItem)
{
	// 인벤토리에 동일한 아이템이 있는지 체크
	uint8 Index = 0;
	bool bIsFound = FindItem(InItem->GetItemID(), 
		Index, 
		[](UItemBase* CheckingItem) 
		{ 
			// InItem이 이미 인벤토리에 있을 때, 
			// 해당 아이템의 갯수가 중복 허용치보다 적은지 체크
			return CheckingItem->Quantity < CheckingItem->GetData()->NumOfDuplicate;
		});

	if (bIsFound)
	{
		// 중복 허용치를 넘지 않은 경우, 병합하기
		uint32 RestAmount = 0;

		if (Items[Index]->TryAddItem(InItem->Quantity, RestAmount))
		{
			OnInventoryUpdated.Broadcast(Index);
			return true;
		}
		else // 나머지가 남은 경우 처리->새로운 인덱스의 슬롯에 할당
			InItem->Quantity = RestAmount;
	}

	// 더 이상 중복 가능한 슬롯이 없는 경우, 새로운 인덱스에 할당
	// false 결과
	// 인벤토리에 공간이 없음, 습득 실패 처리 필요
	return AssignNewItem(InItem);

}

void UInventory::RemoveItem(uint8 InIdx)
{
	if (InIdx >= MaxSize)
		return;

	Items[InIdx] = nullptr;
	OnInventoryUpdated.Broadcast(InIdx);
}

bool UInventory::GetBlankSpace(uint8& OutIndex)
{
	// 빈공간 찾기
	for(uint8 i = 0; i < MaxSize; ++i)
	{
		if (!Items[i])
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}

bool UInventory::FindItem(const FString& InItemID, uint8& OutIndex, TFunction<bool(UItemBase*)> InQuery)
{
	for (uint8 i = 0; i < MaxSize; ++i)
	{
		if (Items[i]->GetItemID() == InItemID)
		{
			if (!InQuery)
			{
				OutIndex = i;
				return true;
			}

			if (InQuery(Items[i]))
			{
				OutIndex = i;
				return true;
			}
			else
				continue;
		}
	}

	return false;
}

bool UInventory::AssignNewItem(UItemBase* InItem)
{
	uint8 Index = 0;
	if (GetBlankSpace(Index))
	{
		Items[Index] = InItem;
		InItem->InventoryIndex = Index;

		OnInventoryUpdated.Broadcast(Index);

		return true;
	}

	// 인벤토리에 공간이 없음
	return false;
}
