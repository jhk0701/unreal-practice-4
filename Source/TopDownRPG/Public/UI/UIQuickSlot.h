// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIQuickSlot.generated.h"

class UUIMenuSlot;

class UQuickSlot;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIQuickSlot : public UUIBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UQuickSlot> BindedQuickSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidgetOptional))
	TObjectPtr<UHorizontalBox> SlotContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement)
	TArray<UUIMenuSlot*> SlotList;

public:
	virtual void NativeOnInitialized() override;

	void Bind(UQuickSlot* InQuickSlot);
	void Clear(uint8 Index);

	void UpdateSlot(uint8 Index);
};
