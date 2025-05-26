// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inherit/PhaseHandler.h"
#include "Inherit/Updatable.h"

#include "BaseState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBaseState : public UObject, public IPhaseHandler, public IUpdatable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	TObjectPtr<class UEnemyFSM> machine;

public:
	UBaseState() {};

	inline virtual void Initialize(UEnemyFSM* InMachine) { machine = InMachine; };

	virtual void Enter() override {};
	virtual void Update(float DeltaTime) override {};
	virtual void Exit() override {};
};
