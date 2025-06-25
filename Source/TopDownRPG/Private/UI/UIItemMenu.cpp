// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIItemMenu.h"

#include <Components/Button.h>


void UUIItemMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UUIItemMenu::Close);
	FuncButton->OnClicked.AddUniqueDynamic(this, &UUIItemMenu::InvokeFunc);
}

void UUIItemMenu::Update(UItemBase* InItem)
{
	SelectedItem = InItem;
}

void UUIItemMenu::InvokeFunc()
{
	Close();
}