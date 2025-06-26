// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWButton.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>


void UTDRPGUWButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button->OnClicked.AddUniqueDynamic(this, &UTDRPGUWButton::InvokeButton);
}

void UTDRPGUWButton::Clear()
{
	ButtonAction.Clear();
}

void UTDRPGUWButton::SetLabel(const FText& InLabel)
{
	Label->SetText(InLabel);
}

void UTDRPGUWButton::InvokeButton()
{
	ButtonAction.Broadcast();
}
