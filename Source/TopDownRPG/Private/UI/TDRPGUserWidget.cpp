// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUserWidget.h"

inline void UTDRPGUserWidget::Open()
{
	SetVisibility(ESlateVisibility::Visible);
}

inline void UTDRPGUserWidget::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}
