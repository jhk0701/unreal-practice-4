// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "Inherit/Bindable.h"
#include "TDRPGUWSkillSlot.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillSlot : public UTDRPGUWSlotBase, public IBindable
{
	GENERATED_BODY()


public:
	void SetKeyText(FText& InText);
	
	virtual void Bind(UDataModel* InModel) override;
	virtual void Unbind() override;
	virtual void Refresh();

protected:
	UPROPERTY()
	TObjectPtr<UDataModel> Model;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyLabel;
};
