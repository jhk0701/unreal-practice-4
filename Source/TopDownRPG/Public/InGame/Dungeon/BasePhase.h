// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inherit/PhaseHandler.h"
#include "BasePhase.generated.h"

class ATDGameState;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBasePhase : public UObject, public IPhaseHandler
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<ATDGameState> State;

public:
	inline void InitPhase(ATDGameState* InState) { State = InState; };

	virtual void Enter() override {};
	virtual void Exit() override {};
};
