// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSkillWindow.generated.h"

class UTDRPGUWSkillSlot;

class UVerticalBox;
class UButton;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillWindow : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWSkillSlot> SlotFactory;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Container;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;
	
};
