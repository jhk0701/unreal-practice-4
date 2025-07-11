// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSkillSlot.h"
#include "TDRPGUWSkillSlotHolder.generated.h"

class USkill;
enum class ESkillInputKey: uint8;
DECLARE_DELEGATE_TwoParams(FOnSkillDropped, USkill*, ESkillInputKey&);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillSlotHolder : public UTDRPGUWSkillSlot
{
	GENERATED_BODY()

public:
	FOnSkillDropped OnSkillDropped;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
