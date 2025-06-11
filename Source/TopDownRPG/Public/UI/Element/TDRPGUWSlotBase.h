// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "Item/ItemBase.h"
#include "TDRPGUWSlotBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotInteractStarted, UItemBase*);
DECLARE_MULTICAST_DELEGATE(FOnSlotInteractCompleted);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSlotBase : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<class UBorder> Background;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<class UImage> IconImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> QuantityLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidgetOptional))
	TObjectPtr<class UButton> SlotButton;

	// 마우스 호버링 이벤트
	// 네이티브 메서드에서 Broadcast 해줄 것
	FOnSlotInteractStarted OnCursorEnter;
	FOnSlotInteractCompleted OnCursorLeave;

	FOnSlotInteractStarted OnButtonClicked;

protected:
	UItemBase* Item = nullptr;

public:
	virtual void SetData(UItemBase* InItem);

	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

protected:
	virtual void Clear();
	virtual void Refresh(UItemBase* InItem);

	void OnIconLoaded(UObject* Loaded);

	UFUNCTION()
	void InvokeButtonClick();
};
