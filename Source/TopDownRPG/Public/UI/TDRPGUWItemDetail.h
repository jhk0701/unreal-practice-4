// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWItemDetail.generated.h"


struct FItemDataRow;
class UItemBase;

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWItemDetail : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIOption")
	FVector2D Size;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIOption")
	bool bShowRarity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIOption")
	bool bShowQuantity;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> NameLabel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityLabel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> RarityTitle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> RarityLabel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> PriceLabel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

public:
	void Update(UItemBase* InItem);
	void Update(FItemDataRow* InData);

	void UpdatePrice(uint32 InPrice);

protected:
	virtual void NativeOnInitialized() override;
};
