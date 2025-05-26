// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGame/Dungeon/BasePhase.h"
#include "EndPhase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UEndPhase : public UBasePhase
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	
};
