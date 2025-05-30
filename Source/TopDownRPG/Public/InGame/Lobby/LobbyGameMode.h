// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void OpenLevel(FName LevelToGo);
	void GoToDungeon();
};
