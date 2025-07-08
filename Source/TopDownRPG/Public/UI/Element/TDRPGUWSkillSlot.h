// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "TDRPGUWSkillSlot.generated.h"

class USkill;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillSlot : public UTDRPGUWSlotBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<USkill> BindedSkill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyLabel;

public:
	void SetKeyText(FText& InText);
	
};
