// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/QuickSlot.h"

#include "TopDownRPG/TopDownRPG.h"

UQuickSlot::UQuickSlot()
{
	Slots.Init(nullptr, QuickSlotMaxSize);
}

bool UQuickSlot::Register(IQuickSlotHandler* InSlot, uint8& OutIndex)
{
	if (GetBlankSpace(OutIndex))
	{
		Slots[OutIndex].SetInterface(InSlot);
		Slots[OutIndex].SetObject(InSlot->_getUObject());

		OnSlotUpdated.Broadcast(OutIndex);
		return true;
	}

	return false;
}

void UQuickSlot::Unregister(uint8 InIdx)
{
	OnSlotUpdated.Broadcast(InIdx);
}

void UQuickSlot::Use(uint8 Idx, AActor* Target)
{
	if (QuickSlotMaxSize <= Idx || !Slots[Idx].GetObject())
		return;

	Slots[Idx]->InvokeSlot(Target);
}

bool UQuickSlot::GetBlankSpace(uint8& OutIndex)
{
	for (uint8 i = 0; i < QuickSlotMaxSize; ++i)
	{
		if (!Slots[i].GetObject())
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}
