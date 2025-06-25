// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIPlayerHUD.generated.h"


/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIPlayerHUD : public UUIBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UUIStatusBar> StatusBar;

	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UUIStatusWindow> StatusWindow;

	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UUIInventory> Inventory;

	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UUIQuickSlot> QuickSlot;

	UPROPERTY(EditAnywhere, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<class UUIEquipment> Equipment;

public:
	virtual void NativeOnInitialized() override;

};
