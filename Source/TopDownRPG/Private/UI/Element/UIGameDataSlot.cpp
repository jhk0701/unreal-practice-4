// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/UIGameDataSlot.h"

#include <Components/Button.h>

void UUIGameDataSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SlotButton->OnClicked.AddUniqueDynamic(this, &UUIGameDataSlot::OnClickButton);
}

void UUIGameDataSlot::OnClickButton()
{
	OnSlotClicked.ExecuteIfBound(SlotName);
}
