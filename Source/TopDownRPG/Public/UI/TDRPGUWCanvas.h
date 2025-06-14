// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWCanvas.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWCanvas : public UTDRPGUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UIElement, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> Canvas;

public:
	class UCanvasPanelSlot* AddToCanvas(UWidget* InChild);
};
