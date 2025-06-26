// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWButton.generated.h"

class UButton;
class UImage;
class UTextBlock;

DECLARE_MULTICAST_DELEGATE(FOnButtonAction);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWButton : public UTDRPGUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Label;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidgetOptional))
	TObjectPtr<UImage> Icon;

public:
	void Clear();
	void SetLabel(const FText& InLabel);
	FOnButtonAction ButtonAction;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void InvokeButton();

};
