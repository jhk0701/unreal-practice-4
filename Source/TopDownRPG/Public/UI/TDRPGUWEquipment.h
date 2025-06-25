// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWEquipment.generated.h"

class UEquipment;
enum class EEquipType : uint8;

class UTDRPGUWEquipmentMenu;
class UTDRPGUWSlotBase;
class UTDRPGUWInventorySlot;
class UButton;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWEquipment : public UTDRPGUserWidget
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
	TMap<EEquipType, UTDRPGUWInventorySlot*> Slots;

	// SubUI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWEquipmentMenu> MenuWindowFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Sub")
	TObjectPtr<UTDRPGUWEquipmentMenu> MenuWindow;

public:
	UTDRPGUWEquipment();
	virtual void NativeOnInitialized() override;
	virtual void Close() override;

	void Bind(UEquipment* InEquipment);
	void UpdateSlot(EEquipType InEquipType);

	void ShowMenu(UTDRPGUWSlotBase* InSlot);
	void HideMenu();
};
