// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIItemMenu.h"
#include "UIInventoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIInventoryMenu : public UUIItemMenu
{
	GENERATED_BODY()

public:
	// TODO : 퀵슬롯 등록 및 해제 -> 드래그앤 드롭 가능하게
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> QuickSlotButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuickSlotLabel;

public:
	virtual void NativeOnInitialized() override;
	virtual void Update(UItemBase* InItem) override;
	virtual void InvokeFunc() override;

	UFUNCTION()
	void RegisterQuickSlot();
	

};
