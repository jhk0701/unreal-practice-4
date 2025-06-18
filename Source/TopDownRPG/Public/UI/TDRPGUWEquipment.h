// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWEquipment.generated.h"

class UEquipment;
enum class EEquipType : uint8;
class UTDRPGUWSlotBase;
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

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UVerticalBox> SlotContainer;

	UPROPERTY(EditAnywhere)
	TMap<EEquipType, UTDRPGUWSlotBase*> Slots;


public:
	virtual void NativeOnInitialized() override;

	void Bind(UEquipment* InEquipment);

	void UpdateSlot(EEquipType InEquipType);
};
