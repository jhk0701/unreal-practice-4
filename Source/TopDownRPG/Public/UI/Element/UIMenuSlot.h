// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/UIInventorySlot.h"
#include "UIMenuSlot.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIMenuSlot : public UUIInventorySlot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<class UTextBlock> IndexLabel;
	
};
