// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIGameDataSlot.generated.h"

class UTextBlock;
class UButton;

DECLARE_DELEGATE_OneParam(FOnSlotClicked, FString&);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIGameDataSlot : public UUIBase
{
	GENERATED_BODY()
	
public:
	int32 Index;

	UPROPERTY()
	FString SlotName;

	FOnSlotClicked OnSlotClicked;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> NumLabel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameLabel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerInfoLabel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;

public:
	virtual void NativeOnInitialized() override;

	inline void InitSlot(int32 InIndex, FString& InSlotName) { Index = InIndex; SlotName = InSlotName; };

private:
	UFUNCTION()
	void OnClickButton();
};
