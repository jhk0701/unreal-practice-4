// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSkillSet.generated.h"

enum class ESkillInputKey : uint8;

class USkillSet;

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
	void Bind(USkillSet* InSkillSet);

protected:
	TObjectPtr<USkillSet> BindedSkillSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWSkillSlotHolder> SlotFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement")
	TMap<ESkillInputKey, UTDRPGUWSkillSlotHolder*> SlotInst;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> Container;

	virtual void NativeOnInitialized() override;
	
};
