// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWQuickSlot.h"
#include "UI/Element/TDRPGUWMenuSlot.h"

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
