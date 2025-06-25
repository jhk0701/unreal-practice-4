// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUWItemMenu.h"
#include "TDRPGUWEquipmentMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWEquipmentMenu : public UTDRPGUWItemMenu
{
	GENERATED_BODY()
	
public:
	virtual void InvokeFunc() override;
};
