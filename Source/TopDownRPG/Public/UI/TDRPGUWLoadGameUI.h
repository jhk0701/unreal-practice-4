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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UScrollBox> SlotContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	TSubclassOf<UTDRPGUWGameDataSlot> SlotFactory;

public:
	// void InitSlot();
};
