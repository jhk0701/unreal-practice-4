// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADungeonGameMode();
	
	void OpenLevel(FName LevelToGo);

	UFUNCTION()
	void GoToLobby();

	UFUNCTION()
	void GoToNextStage();
};
