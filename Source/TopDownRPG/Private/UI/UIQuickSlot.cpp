// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIQuickSlot.h"
#include "UI/Element/UIMenuSlot.h"

#include "Player/QuickSlot.h"
#include "Item/ItemBase.h"

#include <Components/TextBlock.h>
#include <Components/HorizontalBox.h>


void UUIQuickSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!SlotContainer)
		return;

	SlotList.Empty();

 	int32 Cnt =  SlotContainer->GetChildrenCount();
	for (int32 i = 0; i < Cnt; ++i)
	{
		auto* Widget = SlotContainer->GetChildAt(i);

		if (UUIMenuSlot* SlotInst = Cast<UUIMenuSlot>(Widget))
		{
			SlotInst->IndexLabel->SetText(FText::FromString(FString::Printf(TEXT("%d"), i + 1)));
			SlotList.Add(SlotInst);
		}
	}
}


void UUIQuickSlot::Bind(UQuickSlot* InQuickSlot)
{
	BindedQuickSlot = InQuickSlot;
	BindedQuickSlot->OnSlotUpdated.AddUObject(this, &UUIQuickSlot::UpdateSlot);
	
	// 기존에 퀵슬롯에 있는 정보 반영
	uint8 Cnt = InQuickSlot->MAX_SIZE;
	for (uint8 i = 0; i < Cnt; ++i) 
		UpdateSlot(i);
}

void UUIQuickSlot::Clear(uint8 Index)
{
	SlotList[Index]->Clear();
}

void UUIQuickSlot::UpdateSlot(uint8 Index)
{
	if (BindedQuickSlot->Slots[Index].GetInterface() == nullptr)
	{
		Clear(Index);
		return;
	}

	UObject* Handle = BindedQuickSlot->Slots[Index].GetObject();

	if (UItemBase* Item = Cast<UItemBase>(Handle))
	{
		SlotList[Index]->Bind(Item);
	}
}
