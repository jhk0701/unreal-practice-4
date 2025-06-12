// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerInputComponent.h"
#include "PlayerInteraction.generated.h"


/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerInteraction : public UPlayerInputComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "QuickSlot")
	uint8 QuickSlotNumInput = 0;

public:
	UPlayerInteraction();
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;
	
	void InputInteract(const FInputActionValue& Value);
	void InputInventory(const FInputActionValue& Value);
	void InputEquipment(const FInputActionValue& Value);

	// 퀵슬롯 입력
	void TriggerQuickSlot(const FInputActionValue& Value);
	void ReleaseQuickSlot(const FInputActionValue& Value);
	void UseQuickSlot(uint8 Idx);

};

