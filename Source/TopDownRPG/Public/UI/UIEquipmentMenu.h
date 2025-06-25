// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIItemMenu.h"
#include "UIEquipmentMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIEquipmentMenu : public UUIItemMenu
{
	GENERATED_BODY()
	
public:
	virtual void InvokeFunc() override;
};
