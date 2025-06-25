// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UICanvas.h"

#include <Components/CanvasPanel.h>

UCanvasPanelSlot* UUICanvas::AddToCanvas(UWidget* InChild)
{
	return Canvas->AddChildToCanvas(InChild);
}
