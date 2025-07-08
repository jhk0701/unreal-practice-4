// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "TDRPGUWNumericSlot.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWNumericSlot : public UTDRPGUWSlotBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityLabel;
	
public:
	virtual void Clear() override;
};
