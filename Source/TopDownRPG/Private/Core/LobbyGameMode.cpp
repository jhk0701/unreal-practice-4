// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/LobbyGameMode.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameMode::OpenLevel(FName LevelToGo)
{
	UGameplayStatics::OpenLevel(this, LevelToGo);
}

void ALobbyGameMode::GoToDungeon()
{
	OpenLevel(FName("2-Game"));
}
