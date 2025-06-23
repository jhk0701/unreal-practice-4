// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWLoadGameUI.h"

void UTDRPGUWLoadGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitSlots();
}

void UTDRPGUWLoadGameUI::InitSlots()
{
	if (!SlotFactory)  return;

	
}
