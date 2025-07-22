// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWCanvas.generated.h"

class UCanvasPanel;
class UCanvasPanelSlot;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWCanvas : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

public:
	UCanvasPanelSlot* AddToCanvas(UWidget* InChild);
	void SetSort(uint8 InSort);

	virtual void BeginDestroy() override;
};
