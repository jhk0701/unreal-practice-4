// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TitleGameMode.h"
#include "Core/TitleHUD.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#include "CommonConst.h"

ATitleGameMode::ATitleGameMode()
{
	HUDClass = ATitleHUD::StaticClass();
}

void ATitleGameMode::ExitGame()
{
	UWorld* World = GetWorld();

	if(World)
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
		UKismetSystemLibrary::QuitGame(World, Controller, EQuitPreference::Quit, false);
	}
}

void ATitleGameMode::StartGame()
{
	// TODO : 레벨 매니저 추가
	UGameplayStatics::OpenLevel(this, CommonConst::SCENE_LOBBY);
}

void ATitleGameMode::StartNewGame()
{

	StartGame();
}

void ATitleGameMode::ContinueGame()
{

	StartGame();
}
