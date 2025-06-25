// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWLoadGameUI.generated.h"

class UScrollBox;
class UButton;
class UTDRPGUWGameDataSlot;

DECLARE_DELEGATE(FOnDataLoadCompleted);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWLoadGameUI : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	FOnDataLoadCompleted LoadCompleteCallback;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|Scroll")
	int32 ScrollIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIElement|SlotCount")
	int32 SlotCount = 15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UScrollBox> Scroll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	TSubclassOf<UTDRPGUWGameDataSlot> SlotFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement")
	TArray<UTDRPGUWGameDataSlot*> SlotInstances;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Scroll")
	float CurrentOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Scroll")
	float OffsetDelta;

public:
	virtual void NativeOnInitialized() override;

private:
	void InitSlots();
	void ShowScroll(int32 InIndex);

	UFUNCTION()
	void OnScrollChanged(float InOffset);

	void OnSlotClicked(FString& InSlotName);
	void InvokeLoadCompleteCallback();
};
