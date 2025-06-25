// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWMerchantUI.generated.h"

struct FMerchantDataRow;
class UButton;
class UTDRPGUWSlotBase;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWMerchantUI : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> MerchantSideContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> PlayerSideContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	TSubclassOf<UTDRPGUWSlotBase> SlotFactory;

public:
	virtual void NativeOnInitialized() override;

	void SetMerchant(FMerchantDataRow* InMerchantData);
};
