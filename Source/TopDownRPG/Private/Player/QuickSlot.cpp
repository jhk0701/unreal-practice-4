// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/QuickSlot.h"

#include "TopDownRPG/TopDownRPG.h"

UQuickSlot::UQuickSlot()
{
	Slots.Init(nullptr, QuickSlotMaxSize);
}

bool UQuickSlot::Register(IQuickSlotHandler* InSlot)
{
	for(int32 i = 0; i < QuickSlotMaxSize; ++i)
	{
		if (!Slots[i].GetObject())
		{
			Slots[i].SetInterface(InSlot);
			Slots[i].SetObject(InSlot->_getUObject());

			OnSlotRegistered.Broadcast(i);
			return true;
		}
	}

	return false;
}

void UQuickSlot::Use(uint8 Idx, AActor* Target)
{
	if (QuickSlotMaxSize <= Idx || !Slots[Idx].GetObject())
		return;

	Slots[Idx]->InvokeSlot(Target);
}
