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

	void InputAttack(const FInputActionValue& InputValue);
	virtual void InvokeAttack() override;

	void InputSkill(const FInputActionValue& InputValue);
	virtual void InvokeSkill(int32 InValue) override;


	void ActivateHitCollider(bool bIsEnable);
	UFUNCTION()
	void OnActorOverlaped(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
};
