// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "TDRPGUWInventorySlot.generated.h"

class UItemBase;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWInventorySlot : public UTDRPGUWSlotBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UItemBase* Item = nullptr;

public:
	virtual void Clear() override;

	virtual void Bind(UItemBase* InItem);
	inline UItemBase* GetBindedItem() const { return Item; }

protected:
	virtual void InvokeCursorEnter() override;
	virtual void InvokeCursorLeave() override;
	virtual void InvokeButtonClick() override;

	virtual void Refresh(UItemBase* InItem);
	void OnIconLoaded(UObject* Loaded);
};
