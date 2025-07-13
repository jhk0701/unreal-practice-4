// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSkillSet.generated.h"

enum class ESkillInputKey : uint8;

class USkill;
class USkillSet;
class UCharacterAction;

class UTDRPGUWSkillSlotHolder;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillSet : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	void Bind(USkillSet* InSkillSet, UCharacterAction* InAction);

protected:
	TObjectPtr<USkillSet> BindedSkillSet;
	TObjectPtr<UCharacterAction> BindedAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWSkillSlotHolder> SlotFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement")
	TMap<ESkillInputKey, UTDRPGUWSkillSlotHolder*> SlotInst;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> Container;

	virtual void NativeOnInitialized() override;
	void OnSlotUpdated(ESkillInputKey& InKey);
	void OnSkillDropped(USkill* InSkill, ESkillInputKey& InKey);
	
};
