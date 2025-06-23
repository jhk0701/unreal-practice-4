// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWLoadGameUI.generated.h"

class UScrollBox;
class UTDRPGUWGameDataSlot;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWLoadGameUI : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|SlotCount")
	int8 SlotCount = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UScrollBox> SlotContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	TSubclassOf<UTDRPGUWGameDataSlot> SlotFactory;

public:
	virtual void NativeOnInitialized() override;

private:
	void InitSlots();
};
