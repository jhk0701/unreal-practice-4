// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUserWidget.h"

inline void UTDRPGUserWidget::Open()
{
	AddToViewport();
}

inline void UTDRPGUserWidget::Close()
{
	RemoveFromParent();
}
