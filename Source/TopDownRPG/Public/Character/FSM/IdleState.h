// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FSM/BaseState.h"
#include "IdleState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UIdleState : public UBaseState
{
	GENERATED_BODY()
	
public:
	virtual void Enter() override;
	
};
