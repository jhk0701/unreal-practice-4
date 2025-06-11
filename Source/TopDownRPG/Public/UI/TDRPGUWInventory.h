// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWInventory.generated.h"

class UTextBlock;
class UButton;
class UUniformGridPanel;
class UTDRPGUWSlotBase;
class UTDRPGUWItemDetail;
class UTDRPGUWItemMenu;
class UItemBase;


/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWInventory : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	// Header
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	// Body
	UPROPERTY()
	TArray<UTDRPGUWSlotBase*> Slots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> SlotContainer;

	// Footer
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTDRPGUWItemDetail> DetailWindow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTDRPGUWItemMenu> MenuWindow;
	
public:
	virtual void NativeOnInitialized() override;
	void UpdateGold(uint32 Gold);

	void ShowItemDetail(UItemBase* InItem);
	void HideItemDetail();

	void ShowItemMenu(UItemBase* InItem);
	void HideItemMenu();
};
