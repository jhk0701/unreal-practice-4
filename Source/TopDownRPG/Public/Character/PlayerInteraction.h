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

public:
	UPlayerInteraction();
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;
	void InvokeInteract(const FInputActionValue& Value);
};
