// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/QuickSlot.h"

void UQuickSlot::Initialize()
{
	QuickSlot.Init(nullptr, QuickSlotMaxSize);
}

void UQuickSlot::UseQuickSlot(uint8 Idx, AActor* Target)
{
	if (QuickSlotMaxSize <= Idx || !QuickSlot[Idx])
		return;

	QuickSlot[Idx]->InvokeSlot(Target);
}
