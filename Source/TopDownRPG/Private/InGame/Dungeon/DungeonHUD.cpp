// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/DungeonHUD.h"
#include "InGame/Dungeon/DungeonGameState.h"
#include "Core/UIManager.h"
#include "UI/TDRPGUWStageResult.h"
#include <Kismet/GameplayStatics.h>


void ADungeonHUD::ShowResultUI()
{
	UUIManager* UI = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UUIManager>();

	if (UI)
		UI->GetUI<UTDRPGUWStageResult>(FOnLoadCompleted::CreateUObject(this, &ADungeonHUD::InitResultUI));
}

void ADungeonHUD::InitResultUI(UTDRPGUserWidget* ui)
{
	if (UTDRPGUWStageResult* stageResult = Cast<UTDRPGUWStageResult>(ui)) 
	{
		if(ADungeonGameState* gameState = Cast<ADungeonGameState>(UGameplayStatics::GetGameState(GetWorld())))
			stageResult->SetResult(gameState->StageResult == EStageResult::Cleared);
		
		stageResult->AddToViewport();
	}
}
