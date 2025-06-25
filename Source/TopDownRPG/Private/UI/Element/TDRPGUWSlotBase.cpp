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
	// Optional이라 방어코드 추가 // TODO : 이 부분 구조적으로 해결 필요
	if (QuantityLabel)
		QuantityLabel->SetVisibility(ESlateVisibility::Hidden);

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
