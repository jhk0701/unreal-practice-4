// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerInputComponent.h"
#include "PlayerAttack.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerAttack : public UPlayerInputComponent
{
	GENERATED_BODY()

protected:


public:
	UPlayerAttack();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;

	void InputAttack(const FInputActionValue& InputValue);
	void InvokeAttack();

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
