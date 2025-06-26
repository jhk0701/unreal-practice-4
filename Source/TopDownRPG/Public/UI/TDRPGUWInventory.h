// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWInventory.generated.h"

class UPlayerManager;
class UInventory;
class UTextBlock;
class UButton;
class UUniformGridPanel;

class UTDRPGUWSlotBase;
class UTDRPGUWInventorySlot;
class UTDRPGUWItemDetail;
class UTDRPGUWInventoryMenu;


/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWInventory : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UInventory> BindedInventory;

	// Header
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	// Body
	UPROPERTY()
	TArray<UTDRPGUWInventorySlot*> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> SlotContainer;

	// Footer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldLabel;

	// Sub UIs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWItemDetail> DetailWindowFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UTDRPGUWItemDetail> DetailWindow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWInventoryMenu> MenuWindowFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UTDRPGUWInventoryMenu> MenuWindow;

public:
	UTDRPGUWInventory();
	virtual void NativeOnInitialized() override;
	virtual void Close() override;

	void Bind(UPlayerManager* InManager);

	void UpdateInventory(uint8 Index);
	void UpdateGold(uint32 Gold);

	void ShowItemDetail(UTDRPGUWSlotBase* InSlot);
	void HideItemDetail();

	void ShowItemMenu(UTDRPGUWSlotBase* InSlot);
	void HideItemMenu();

protected:
	void InitSubWidget();
};
