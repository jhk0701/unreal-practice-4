// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWNumericSlot.h"

#include <Components/TextBlock.h>

void UTDRPGUWNumericSlot::Clear()
{
	Super::Clear();

	QuantityLabel->SetVisibility(ESlateVisibility::Hidden);
}
