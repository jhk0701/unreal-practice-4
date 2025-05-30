// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DungeonGameMode.h"
#include "Core/DungeonGameState.h"
#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"


ADungeonGameMode::ADungeonGameMode()
{
	GameStateClass = ADungeonGameState::StaticClass();
	PlayerControllerClass = ATDRPGPlayerController::StaticClass();
	DefaultPawnClass = ATDRPGPlayer::StaticClass();
}
