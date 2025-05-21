// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TDRPGInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
};
