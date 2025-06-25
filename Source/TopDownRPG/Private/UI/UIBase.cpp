// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBase.h"


void UUIBase::Open()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UUIBase::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UUIBase::Toggle()
{
	IsVisible() ? Close() : Open();
}
