// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWGameDataSlot.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWGameDataSlot : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> NumLabel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameLabel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerInfoLabel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;
};
