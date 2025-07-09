// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWPlayerUI.generated.h"

class UTDRPGUWStatusBar;
class UTDRPGUWQuickSlot;
class UTDRPGUWSkillSet;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWPlayerUI : public UTDRPGUserWidget
{	
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTDRPGUWStatusBar> StatusBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTDRPGUWQuickSlot> QuickSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTDRPGUWSkillSet> SkillSet;
};
