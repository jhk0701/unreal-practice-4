// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNRPG_API IEnemyState
{
	GENERATED_BODY()

public:
	virtual void Enter() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Exit() = 0;

};
