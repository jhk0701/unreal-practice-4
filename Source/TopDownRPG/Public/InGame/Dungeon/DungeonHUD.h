// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TDRPGHUD.h"
#include "DungeonHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ADungeonHUD : public ATDRPGHUD
{
	GENERATED_BODY()
	
public:
	void ShowResultUI();
	void InitResultUI(class UTDRPGUserWidget* ui);
};
