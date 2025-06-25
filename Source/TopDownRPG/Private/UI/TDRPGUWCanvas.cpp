// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWCanvas.h"

#include <Components/CanvasPanel.h>

UCanvasPanelSlot* UTDRPGUWCanvas::AddToCanvas(UWidget* InChild)
{
	return Canvas->AddChildToCanvas(InChild);
}
