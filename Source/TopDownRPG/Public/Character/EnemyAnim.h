// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterAnimBase.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UEnemyAnim : public UCharacterAnimBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnAttackStarted();
	UFUNCTION(BlueprintCallable)
	void OnAttackEnded();

protected:
	virtual void SetAccel(const APawn* Pawn) override;
	virtual void SetIsDead(const APawn* Pawn) override;

};
