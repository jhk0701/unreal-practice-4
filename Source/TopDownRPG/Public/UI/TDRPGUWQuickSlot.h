// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWQuickSlot.generated.h"

class UQuickSlot;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWQuickSlot : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UQuickSlot> BindedQuickSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidgetOptional))
	TObjectPtr<class UHorizontalBox> SlotContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement)
	TArray<class UTDRPGUWSlotBase*> SlotList;

public:
	virtual void NativeOnInitialized() override;

	void Bind(class UQuickSlot* InQuickSlot);
	void UpdateSlot(uint8 Index);
};
