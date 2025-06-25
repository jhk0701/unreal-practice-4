// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UITitle.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS(BlueprintType)
class TOPDOWNRPG_API UUITitle : public UUIBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleLabel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

public:
	virtual void NativeOnInitialized() override;
	void BindButton();
};
