// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "Inherit/Bindable.h"
#include "TDRPGUWSkillSlot.generated.h"

class USkill;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillSlot : public UTDRPGUWSlotBase, public IBindable
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<USkill> BindedSkill;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyLabel;

public:
	void SetKeyText(FText& InText);
	
	void Bind(UDataModel* InModel) override;

	void Unbind() override;

	void Refresh(UDataModel* InModel) override;

};
