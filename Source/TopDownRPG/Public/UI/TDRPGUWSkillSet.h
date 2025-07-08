// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSkillSet.generated.h"

enum class ESkillInputKey : uint8;

class UTDRPGUWSkillSlot;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillSet : public UTDRPGUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWSkillSlot> SlotFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement")
	TMap<ESkillInputKey, UTDRPGUWSkillSlot*> SlotInst;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> Container;

protected:
	virtual void NativeOnInitialized() override;
	
};
