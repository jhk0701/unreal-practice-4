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
	FTimerHandle attackResetTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float resetInterval = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Combo")
	int32 attackCount = 0;

public:
	UPlayerAttack();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;

	void InputAttack(const FInputActionValue& InputValue);
	void InvokeAttack();
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
