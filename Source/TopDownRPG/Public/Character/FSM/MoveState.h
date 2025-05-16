// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FSM/BaseState.h"
#include "MoveState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UMoveState : public UBaseState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
};
