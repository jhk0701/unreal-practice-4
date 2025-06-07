// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "Item/ItemBase.h"
#include "TDRPGUWSlotBase.generated.h"

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

protected:
	UItemBase* Item = nullptr;

public:
	virtual void NativeOnInitialized() override;
	virtual void Clear();
	virtual void SetData(UItemBase* InItem);
	virtual void Update();
};
