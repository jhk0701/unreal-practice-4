// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWGameDataSlot.generated.h"

class UTextBlock;
class UButton;

DECLARE_DELEGATE_OneParam(FOnSlotClicked, FString&);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWGameDataSlot : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	int32 Index;

	UPROPERTY()
	FString SlotName;

	FOnSlotClicked OnSlotClicked;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NumLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerInfoLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;

public:
	virtual void NativeOnInitialized() override;

	inline void InitSlot(int32 InIndex, FString& InSlotName) { Index = InIndex; SlotName = InSlotName; };

private:
	UFUNCTION()
	void OnClickButton();
};
