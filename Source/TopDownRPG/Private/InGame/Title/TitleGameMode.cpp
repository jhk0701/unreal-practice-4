// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Title/TitleGameMode.h"
#include "Core/TDRPGHUD.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#include "CommonConst.h"

ATitleGameMode::ATitleGameMode()
{
	HUDClass = ATDRPGHUD::StaticClass();
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
	// 비동기 로딩 기능
	UGameplayStatics::OpenLevel(this, CommonConst::SCENE_LOBBY);
}

void ATitleGameMode::StartNewGame()
{
	// TODO : 새로운 게임 데이터
	// 새 게임 시작 -> 클래스 선택 UI
	// 아직 클래스가 없음
	// PlayerName 이름 입력

	StartGame();
}

void ATitleGameMode::ContinueGame()
{
	// TODO : 이전 게임 데이터 로드
	// 게임 데이터 UI

	StartGame();
}
