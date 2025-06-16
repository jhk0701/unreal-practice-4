// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWQuickSlot.h"
#include "UI/Element/TDRPGUWMenuSlot.h"

#include "Player/QuickSlot.h"
#include "Item/ItemBase.h"

#include <Components/TextBlock.h>
#include <Components/HorizontalBox.h>


void UTDRPGUWQuickSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!SlotContainer)
		return;

	SlotList.Empty();

 	int32 Cnt =  SlotContainer->GetChildrenCount();
	for (int32 i = 0; i < Cnt; ++i)
	{
		auto* Widget = SlotContainer->GetChildAt(i);

		if (UTDRPGUWMenuSlot* SlotInst = Cast<UTDRPGUWMenuSlot>(Widget))
		{
			SlotInst->IndexLabel->SetText(FText::FromString(FString::Printf(TEXT("%d"), i + 1)));
			SlotList.Add(SlotInst);
		}
	}
}


void UTDRPGUWQuickSlot::Bind(UQuickSlot* InQuickSlot)
{
	BindedQuickSlot = InQuickSlot;
	BindedQuickSlot->OnSlotRegistered.AddUObject(this, &UTDRPGUWQuickSlot::UpdateSlot);
	
	// 기존에 퀵슬롯에 있는 정보 반영
	uint8 Cnt = InQuickSlot->QuickSlotMaxSize;
	for (uint8 i = 0; i < Cnt; ++i) 
		UpdateSlot(i);
}

void UTDRPGUWQuickSlot::UpdateSlot(uint8 Index)
{
	if (BindedQuickSlot->Slots[Index].GetInterface() == nullptr)
		return;

	UObject* Handle = BindedQuickSlot->Slots[Index].GetObject();

	if (UItemBase* Item = Cast<UItemBase>(Handle))
	{
		SlotList[Index]->SetData(Item);
	}
}
