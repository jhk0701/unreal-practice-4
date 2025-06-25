// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UICanvas.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUICanvas : public UUIBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UIElement, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> Canvas;

public:
	class UCanvasPanelSlot* AddToCanvas(UWidget* InChild);
};
