// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWCanvas.h"

#include <Components/CanvasPanel.h>

#include "TopDownRPG/TopDownRPG.h"

UCanvasPanelSlot* UTDRPGUWCanvas::AddToCanvas(UWidget* InChild)
{
	return Canvas->AddChildToCanvas(InChild);
}

void UTDRPGUWCanvas::SetSort(uint8 InSort)
{
}

void UTDRPGUWCanvas::BeginDestroy()
{
	Super::BeginDestroy();

	PRINT_LOG(TEXT("Canvas Begin Destroy"));
}
