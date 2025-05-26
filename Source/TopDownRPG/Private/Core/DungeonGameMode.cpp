// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DungeonGameMode.h"
#include "Core/DungeonGameState.h"
#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"
#include "CommonConst.h"
#include <Kismet/GameplayStatics.h>


ADungeonGameMode::ADungeonGameMode()
{
	GameStateClass = ADungeonGameState::StaticClass();
	PlayerControllerClass = ATDRPGPlayerController::StaticClass();
	DefaultPawnClass = ATDRPGPlayer::StaticClass();
}

void ADungeonGameMode::OpenLevel(FName LevelToGo)
{
	UGameplayStatics::OpenLevel(this, LevelToGo);
}

void ADungeonGameMode::GoToLobby()
{
	OpenLevel(CommonConst::SCENE_LOBBY);
}
