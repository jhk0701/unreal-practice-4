// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/EndPhase.h"
#include "InGame/Dungeon/DungeonHUD.h"
#include "Core/TDGameState.h"

#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>

void UEndPhase::Enter()
{
	// 스테이지 종료 UI
	APlayerController* controller = UGameplayStatics::GetPlayerController(State->GetWorld(), 0);
	
	if(ADungeonHUD* hud = Cast<ADungeonHUD>(controller->GetHUD()))
	{
		hud->ShowResultUI();
	}

	// TODO : 스테이지 보상
}
