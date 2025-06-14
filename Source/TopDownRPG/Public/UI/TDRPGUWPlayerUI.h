// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWPlayerUI.generated.h"


/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWPlayerUI : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UTDRPGUWQuickSlot> QuickSlot;
	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UTDRPGUWStatusBar> StatusBar;
	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UTDRPGUWEquipment> Equipment;
	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UTDRPGUWInventory> Inventory;

public:
	virtual void NativeOnInitialized() override;

};
