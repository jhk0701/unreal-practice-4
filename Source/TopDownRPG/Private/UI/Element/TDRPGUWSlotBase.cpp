// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSlotBase.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

void UTDRPGUWSlotBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Clear();
}

void UTDRPGUWSlotBase::Clear()
{
	QuantityLabel->SetVisibility(ESlateVisibility::Hidden);
	
	IconImage->SetVisibility(ESlateVisibility::Hidden);
	IconImage->SetBrushResourceObject(nullptr);
}

void UTDRPGUWSlotBase::SetData(UItemBase* InItem)
{
	Item = InItem;
	Update();
}

void UTDRPGUWSlotBase::Update()
{
	if (!Item)
		return;


}
