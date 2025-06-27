// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/QuickSlot.h"

UQuickSlot::UQuickSlot()
{
	Slots.Init(nullptr, MAX_SIZE);
}

void UQuickSlot::InitSlot(uint8 InIndex, IQuickSlotHandler* InSlot)
{
	if (!InSlot)
		return;

	Slots[InIndex].SetInterface(InSlot);
	Slots[InIndex].SetObject(InSlot->_getUObject());

	InSlot->RegisterSlot(InIndex);
}

bool UQuickSlot::Register(IQuickSlotHandler* InSlot)
{
	uint8 Index;
	if (GetBlankSpace(Index))
	{
		Slots[Index].SetInterface(InSlot);
		Slots[Index].SetObject(InSlot->_getUObject());

		InSlot->RegisterSlot(Index);

		OnSlotUpdated.Broadcast(Index);

		return true;
	}

	return false;
}

void UQuickSlot::Unregister(uint8 InIdx)
{
	if (InIdx >= MAX_SIZE)
		return;

	if (!Slots[InIdx].GetObject())
		return;

	Slots[InIdx]->UnregisterSlot();
	
	Slots[InIdx].SetInterface(nullptr);
	Slots[InIdx].SetObject(nullptr);

	OnSlotUpdated.Broadcast(InIdx);
}

void UQuickSlot::Use(uint8 Idx, AActor* Target)
{
	if (MAX_SIZE <= Idx || !Slots[Idx].GetObject())
		return;

	Slots[Idx]->InvokeSlot(Target);
}

bool UQuickSlot::GetBlankSpace(uint8& OutIndex)
{
	for (uint8 i = 0; i < MAX_SIZE; ++i)
	{
		if (!Slots[i].GetObject())
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}
