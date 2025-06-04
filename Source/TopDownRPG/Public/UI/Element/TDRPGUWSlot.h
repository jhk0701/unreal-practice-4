// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSlot.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSlot : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta=(BindWidget))
	TObjectPtr<UImage> BackImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UImage> ThumbnailImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> QuantityLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> SlotNumLabel;
};
