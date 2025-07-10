// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSkillWindow.generated.h"

class UPlayerAction;
class UTDRPGUWSkillListSlot;

class UScrollBox;
class UButton;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillWindow : public UTDRPGUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UPlayerAction> BindedAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWSkillListSlot> SlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TArray<UTDRPGUWSkillListSlot*> ListSlots;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> Container;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;
	
public:
	virtual void NativeOnInitialized() override;

	void Bind(UPlayerAction* InPlayerAction);
	void Refresh();
};
