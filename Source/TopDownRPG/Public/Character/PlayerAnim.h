// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterAnimBase.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerAnim : public UCharacterAnimBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
	int32 CurAttackIdx;

public:
	virtual void PlayAttack(int32 Idx) override;
	virtual void PlayHit() override;

	UFUNCTION(BlueprintCallable)
	void OnAttackStarted();
	UFUNCTION(BlueprintCallable)
	void OnAttackEnded();

protected:
	virtual void SetIsDead(const APawn* Pawn) override;
};
