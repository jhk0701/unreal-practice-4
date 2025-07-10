// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSkillSlot.h"
#include "TDRPGUWSkillListSlot.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillListSlot : public UTDRPGUWSkillSlot
{
	GENERATED_BODY()

public:
	virtual void Bind(UDataModel* InModel) override;
	virtual void Refresh() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InputLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CostLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownLabel;
};
