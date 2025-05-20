// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimBase.generated.h"

class UAnimMontage;


UCLASS()
class TOPDOWNRPG_API UCharacterAnimBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Accel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float AccelScaler = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> hitMontage;

public:
	virtual void PlayAttack(const int32 Idx);
	virtual bool IsAttackPlaying() const { return Montage_IsPlaying(attackMontage); };
	virtual void PlayHit();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void SetAccel(const APawn* Pawn);
	virtual void SetIsDead(const APawn* Pawn);
};
