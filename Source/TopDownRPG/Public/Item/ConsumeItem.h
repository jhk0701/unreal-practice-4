// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "Inherit/QuickSlotHandler.h"
#include "ConsumeItem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UConsumeItem : public UItemBase, public IQuickSlotHandler
{
	GENERATED_BODY()

public:
	ETableType GetItemType() override;

	void InvokeSlot(AActor* Subject) override;
	uint8 GetIndex() override;

	void Use(AActor* Subject);

};
