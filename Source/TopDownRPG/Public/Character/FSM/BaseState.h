// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/FSM/EnemyState.h"
#include "BaseState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBaseState : public UObject, public IEnemyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	TObjectPtr<class UEnemyFSM> machine;

public:
	UBaseState();

	virtual void Initialize(UEnemyFSM* InMachine) { machine = InMachine; };

	virtual void Enter() override {};
	virtual void Update(float DeltaTime) override {};
	virtual void Exit() override {};
};
