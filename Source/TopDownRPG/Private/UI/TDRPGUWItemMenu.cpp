// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWItemMenu.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>

void UTDRPGUWItemMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWItemMenu::Close);
}

void UTDRPGUWItemMenu::Update(UItemBase* InItem)
{
}

void UTDRPGUWItemMenu::RegisterQuickSlot()
{
}

void UTDRPGUWItemMenu::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}
