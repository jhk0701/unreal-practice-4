// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Lobby/LobbyGameMode.h"
#include "TDRPGConst.h"
#include <Kismet/GameplayStatics.h>

void ALobbyGameMode::OpenLevel(FName LevelToGo)
{
	UGameplayStatics::OpenLevel(this, LevelToGo);
}

void ALobbyGameMode::GoToDungeon()
{
	OpenLevel(FTDRPGConst::SCENE_GAME);
}
