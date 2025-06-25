// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWInventorySlot.h"
#include "TDRPGUWMenuSlot.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWMenuSlot : public UTDRPGUWInventorySlot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<class UTextBlock> IndexLabel;
	
};
