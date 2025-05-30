// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATitleGameMode();

	UFUNCTION()
	void ExitGame();
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void StartNewGame();
	UFUNCTION()
	void ContinueGame();
};
