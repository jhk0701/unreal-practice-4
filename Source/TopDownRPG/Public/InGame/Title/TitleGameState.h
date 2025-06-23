// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TDRPGGameState.h"
#include "TitleGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATitleGameState : public ATDRPGGameState
{
	GENERATED_BODY()

public:
	// 필요 시 분리
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NewGame")
	FString NewClassID;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NewGame")
	FString NewPlayerName;
};
