// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIEquipment.generated.h"

class UEquipment;
enum class EEquipType : uint8;

class UUIEquipmentMenu;
class UUISlotBase;
class UUIInventorySlot;

class UButton;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIEquipment : public UUIBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UEquipment> BindedEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UVerticalBox> SlotContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement")
	TMap<EEquipType, UUIInventorySlot*> Slots;

	// SubUI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Factory")
	TSubclassOf<UUIEquipmentMenu> MenuWindowFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Sub")
	TObjectPtr<UUIEquipmentMenu> MenuWindow;

public:
	UUIEquipment();
	virtual void NativeOnInitialized() override;
	virtual void Close() override;

	void Bind(UEquipment* InEquipment);
	void UpdateSlot(EEquipType InEquipType);

	void ShowMenu(UUISlotBase* InSlot);
	void HideMenu();
};
