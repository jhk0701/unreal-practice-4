// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Title/TitleGameMode.h"
#include "InGame/Title/TitleGameState.h"

#include "CommonConst.h"
#include "Core/TDRPGHUD.h"
#include "Core/UIManager.h"
#include "UI/TDRPGUWNewGameUI.h"
#include "UI/TDRPGUWLoadGameUI.h"

#include "Core/PlayerDataManager.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#include <Misc/Paths.h>
#include <HAL/PlatformFile.h>
#include <HAL/PlatformFileManager.h>

#include "TopDownRPG/TopDownRPG.h"


ATitleGameMode::ATitleGameMode()
{
	HUDClass = ATDRPGHUD::StaticClass();
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
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
	// TODO : 비동기 로딩 기능
	UGameplayStatics::OpenLevel(this, CommonConst::SCENE_LOBBY);
}

void ATitleGameMode::StartNewGame()
{
	// 새 게임 시작 UI
	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();
	UI->GetUI<UTDRPGUWNewGameUI>()->Open();
}

void ATitleGameMode::CreateNewGameData(const FString& InClassID, const FString& InName)
{
	// 새로운 게임 데이터
	UPlayerDataManager* PlayerData = GetGameInstance()->GetSubsystem<UPlayerDataManager>();
	PlayerData->CreateData(InName, InClassID);

	StartGame();
}


void ATitleGameMode::ContinueGame()
{
	// TODO
	// 1. 이전 게임 데이터 로드
	ATitleGameState* State = GetGameState<ATitleGameState>();
	if (State) 
	{
		FString SaveDir = FPaths::ProjectSavedDir() / TEXT("SaveGames");
		// PRINT_LOG(TEXT("[SaveDir] %s"), *SaveDir);
		// IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		// IPlatformFile::FDirectoryVisitor* Visitor = new 

		return;
	}
	
	// 2. 게임 데이터 UI
	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();
	UI->GetUI<UTDRPGUWLoadGameUI>()->Open();

	// UI에 로드한 데이터 리스트 전달
	
	// StartGame();
}
