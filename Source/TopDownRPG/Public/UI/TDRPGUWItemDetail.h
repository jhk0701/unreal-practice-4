// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWItemDetail.generated.h"

class UTextBlock;
class UImage;
class UItemBase;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWItemDetail : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> NameLabel;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityLabel;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> RarityLabel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	void Update(const UItemBase* InItem);
};
