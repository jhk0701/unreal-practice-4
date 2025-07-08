// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSlotBase.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Components/Button.h>


void UTDRPGUWSlotBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SlotButton)
		SlotButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWSlotBase::InvokeButtonClick);

	Clear();
}

void UTDRPGUWSlotBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	InvokeCursorEnter();
}

void UTDRPGUWSlotBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	InvokeCursorLeave();
}


void UTDRPGUWSlotBase::Clear()
{
	IconImage->SetVisibility(ESlateVisibility::Hidden);
	IconImage->SetBrushResourceObject(nullptr);
}

void UTDRPGUWSlotBase::InvokeCursorEnter()
{
	OnCursorEnter.Broadcast(this);
}

void UTDRPGUWSlotBase::InvokeCursorLeave()
{
	OnCursorLeave.Broadcast();
}

void UTDRPGUWSlotBase::InvokeButtonClick(){}
