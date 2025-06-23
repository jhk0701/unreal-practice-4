// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWGameDataSlot.h"
#include <Components/Button.h>

void UTDRPGUWGameDataSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SlotButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWGameDataSlot::OnClickButton);
}

void UTDRPGUWGameDataSlot::OnClickButton()
{
	OnSlotClicked.ExecuteIfBound(SlotName);
}
