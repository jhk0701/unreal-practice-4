// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "Item/ItemBase.h"
#include "TDRPGUWSlotBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMouseEnterDelegate, UItemBase*);
DECLARE_MULTICAST_DELEGATE(FOnMouseLeaveDelegate);

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

	// 마우스 호버링 이벤트
	// 네이티브 메서드에서 Broadcast 해줄 것
	FOnMouseEnterDelegate OnMouseEnterEvent;
	FOnMouseLeaveDelegate OnMouseLeaveEvent;

protected:
	UItemBase* Item = nullptr;

public:
	virtual void SetData(UItemBase* InItem);

	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

protected:
	virtual void Clear();
	virtual void Refresh();

	void OnIconLoaded(UObject* Loaded);
};
