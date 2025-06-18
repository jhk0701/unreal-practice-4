// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWItemMenu.h"

#include <Components/Button.h>


void UTDRPGUWItemMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWItemMenu::Close);
	FuncButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWItemMenu::InvokeFunc);
}

void UTDRPGUWItemMenu::Update(UItemBase* InItem)
{
	SelectedItem = InItem;
}

void UTDRPGUWItemMenu::InvokeFunc()
{
	Close();
}