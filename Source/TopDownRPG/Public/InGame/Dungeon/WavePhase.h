// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGame/Dungeon/BasePhase.h"
#include "WavePhase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UWavePhase : public UBasePhase
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	virtual void Exit() override;
};
