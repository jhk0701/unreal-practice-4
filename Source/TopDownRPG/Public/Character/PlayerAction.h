// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterAction.h"
#include "Character/Input/InputHandler.h"
#include "PlayerAction.generated.h"

class USkill;
class UActiveSkill;

class ATDRPGPlayer;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerAction : public UCharacterAction, public IInputHandler
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Owner")
	TObjectPtr<ATDRPGPlayer> Player;

public:
	UPlayerAction();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;
	
	void OnPlayerInitialized();
	virtual void InvokeAttack() override;
	virtual void InvokeSkill(uint32 InIndex) override;
	virtual void InvokeLaunch() override;

	virtual bool TryUseResource(const TMap<EStatus, int32>& InRequirement) override;
	
	void InputAttack(const FInputActionValue& InputValue);
	void InputSkill(const FInputActionValue& InputValue);
};
