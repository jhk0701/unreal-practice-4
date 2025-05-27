// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DungeonHUD.h"
#include "Core/UISubsystem.h"
#include "Core/DungeonGameState.h"
#include "UI/TDRPGUWStageResult.h"
#include <Kismet/GameplayStatics.h>


void ADungeonHUD::ShowResultUI()
{
	UUISubsystem* uiSys = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UUISubsystem>();

	if (uiSys)
		uiSys->GetUI<UTDRPGUWStageResult>(FOnLoadCompleted::CreateUObject(this, &ADungeonHUD::InitResultUI));
}

void ADungeonHUD::InitResultUI(UTDRPGUserWidget* ui)
{
	if (UTDRPGUWStageResult* stageResult = Cast<UTDRPGUWStageResult>(ui)) 
	{
		if(ADungeonGameState* gameState = Cast<ADungeonGameState>(UGameplayStatics::GetGameState(GetWorld())))
		{
			stageResult->SetResult(gameState->StageResult == EStageResult::Cleared);
		}
		
		stageResult->AddToViewport();
	}
}
