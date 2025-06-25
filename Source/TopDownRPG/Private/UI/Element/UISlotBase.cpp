// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/UISlotBase.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Components/Button.h>


void UUISlotBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SlotButton)
		SlotButton->OnClicked.AddUniqueDynamic(this, &UUISlotBase::InvokeButtonClick);

	Clear();
}

void UUISlotBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	InvokeCursorEnter();
}

void UUISlotBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	InvokeCursorLeave();
}


void UUISlotBase::Clear()
{
	// Optional이라 방어코드 추가 // TODO : 이 부분 구조적으로 해결 필요
	if (QuantityLabel)
		QuantityLabel->SetVisibility(ESlateVisibility::Hidden);

	IconImage->SetVisibility(ESlateVisibility::Hidden);
	IconImage->SetBrushResourceObject(nullptr);
}

void UUISlotBase::InvokeCursorEnter()
{
	OnCursorEnter.Broadcast(this);
}

void UUISlotBase::InvokeCursorLeave()
{
	OnCursorLeave.Broadcast();
}

void UUISlotBase::InvokeButtonClick(){}
