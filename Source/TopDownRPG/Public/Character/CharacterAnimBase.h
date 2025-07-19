// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimBase.generated.h"

class UAnimMontage;

DECLARE_MULTICAST_DELEGATE(FAnimNotify);

UCLASS()
class TOPDOWNRPG_API UCharacterAnimBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Accel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AccelScaler = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> HitMontage;

	// 동적으로 주입해서 쓸 것
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Montage")
	TObjectPtr<UAnimMontage> AttackMontage;

public:
	FAnimNotify OnHitStarted;
	FAnimNotify OnHitEnded;
	FAnimNotify OnLaunchInvoked;

	virtual void PlayAttack(UAnimMontage* InMontage, const FString& InFmt);
	virtual void PlayAttackLast() {};
	virtual bool IsAttackPlaying() const { return Montage_IsPlaying(AttackMontage); };
	
	virtual void PlayHit();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void SetAccel(const APawn* Pawn);
	virtual void SetIsDead(const APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	virtual void NotifyHitStart();

	UFUNCTION(BlueprintCallable)
	virtual void NotifyHitEnd();

	UFUNCTION(BlueprintCallable)
	virtual void NotifyLaunchInvoke();
};
