// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TDRPGGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATDRPGGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// 플레이어 접근용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	TWeakObjectPtr<class ATDRPGPlayer> Player;
};
