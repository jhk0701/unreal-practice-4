// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimBase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UCharacterAnimBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Accel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float AccelScaler = 500.f;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void SetAccel(const APawn* Pawn);
};
