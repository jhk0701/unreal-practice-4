// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "Inherit/Bindable.h"
#include "TDRPGUWInventorySlot.generated.h"

class UDataModel;
class UItemBase;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWInventorySlot : public UTDRPGUWSlotBase, public IBindable
{
	GENERATED_BODY()

public:
	virtual void Clear() override;

	virtual void Bind(UDataModel* InModel) override;
	virtual void Bind(UItemBase* InItem);
	virtual void Unbind() override;
	virtual void Refresh(UDataModel* InModel);

	UItemBase* GetItem() const;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityLabel;

	virtual void InvokeCursorEnter() override;
	virtual void InvokeCursorLeave() override;
	virtual void InvokeButtonClick() override;

	void OnIconLoaded(UObject* Loaded);

};
