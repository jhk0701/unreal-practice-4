// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIInventory.generated.h"

class UPlayerManager;
class UInventory;
class UTextBlock;
class UButton;
class UUniformGridPanel;

class UUISlotBase;
class UUIInventorySlot;
class UUIItemDetail;
class UUIInventoryMenu;


/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIInventory : public UUIBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UInventory> BindedInventory;

	// Header
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	// Body
	UPROPERTY()
	TArray<UUIInventorySlot*> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> SlotContainer;

	// Footer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldLabel;

	// Sub UIs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Factory")
	TSubclassOf<UUIItemDetail> DetailWindowFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UUIItemDetail> DetailWindow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Factory")
	TSubclassOf<UUIInventoryMenu> MenuWindowFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UUIInventoryMenu> MenuWindow;

public:
	UUIInventory();
	virtual void NativeOnInitialized() override;
	virtual void Close() override;

	void Bind(UPlayerManager* InManager);

	void UpdateInventory(uint8 Index);
	void UpdateGold(uint32 Gold);

	void ShowItemDetail(UUISlotBase* InSlot);
	void HideItemDetail();

	void ShowItemMenu(UUISlotBase* InSlot);
	void HideItemMenu();

protected:
	void InitSubWidget();
};
