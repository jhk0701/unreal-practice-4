// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIButton.generated.h"

class UButton;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIButton : public UUIBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Label;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidgetOptional))
	TObjectPtr<UImage> Icon;
};
