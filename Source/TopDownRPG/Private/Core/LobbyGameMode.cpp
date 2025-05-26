// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/LobbyGameMode.h"
#include "CommonConst.h"
#include <Kismet/GameplayStatics.h>

void ALobbyGameMode::OpenLevel(FName LevelToGo)
{
	UGameplayStatics::OpenLevel(this, LevelToGo);
}

void ALobbyGameMode::GoToDungeon()
{
	OpenLevel(CommonConst::SCENE_GAME);
}
