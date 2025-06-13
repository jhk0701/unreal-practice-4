// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUserWidget.h"

void UTDRPGUserWidget::Open()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UTDRPGUserWidget::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UTDRPGUserWidget::Toggle()
{
	IsVisible() ? Close() : Open();
}
