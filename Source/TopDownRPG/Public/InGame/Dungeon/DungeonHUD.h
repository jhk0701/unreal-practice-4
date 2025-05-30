// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DungeonHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ADungeonHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void ShowResultUI();
	void InitResultUI(class UTDRPGUserWidget* ui);
};
