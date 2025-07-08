// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSlotBase.generated.h"

class UBorder;
class UImage;
class UTextBlock;
class UButton;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotInteractStarted, UTDRPGUWSlotBase*);
DECLARE_MULTICAST_DELEGATE(FOnSlotInteractCompleted);

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API UTDRPGUWSlotBase : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void Clear();

	// 마우스 호버링 이벤트
	// 네이티브 메서드에서 Broadcast 해줄 것
	FOnSlotInteractStarted OnCursorEnter;

	FOnSlotInteractCompleted OnCursorLeave;

	// 슬롯에 대한 클릭 이벤트
	FOnSlotInteractStarted OnButtonClicked;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Background;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;


	virtual void InvokeCursorEnter();

	virtual void InvokeCursorLeave();

	UFUNCTION()
	virtual void InvokeButtonClick();
};

