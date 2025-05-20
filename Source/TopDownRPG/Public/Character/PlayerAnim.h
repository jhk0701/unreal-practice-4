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

public:
	virtual void PlayAttack(int32 Idx) override;
	virtual void PlayHit() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
	int curAttack;

	virtual void SetIsDead(const APawn* Pawn) override;
};
