// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/QuickSlot.h"


void UQuickSlot::Initialize()
{
	Slots.Init(nullptr, QuickSlotMaxSize);
}

bool UQuickSlot::Register(IQuickSlotHandler* InSlot)
{
	for(int32 i = 0; i < QuickSlotMaxSize; ++i)
	{
		if (!Slots[i].GetInterface())
		{
			Slots[i].SetInterface(InSlot);
			OnSlotRegistered.Broadcast(i);
			return true;
		}
	}

	return false;
}

void UQuickSlot::Use(uint8 Idx, AActor* Target)
{
	if (QuickSlotMaxSize <= Idx || !Slots[Idx].GetInterface())
		return;

	Slots[Idx]->InvokeSlot(Target);
}
