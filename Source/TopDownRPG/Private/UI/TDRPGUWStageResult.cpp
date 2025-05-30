// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWStageResult.h"
#include "InGame/Dungeon/DungeonGameMode.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>


void UTDRPGUWStageResult::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindButton();
}

void UTDRPGUWStageResult::SetResult(bool bIsCleared)
{
	ResultLabel->SetText(bIsCleared ? FText::FromString(TEXT("Stage Cleared")) : FText::FromString(TEXT("Stage Failed")));
}

void UTDRPGUWStageResult::BindButton()
{
	ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());

	if (!gameMode)
		return;

	NextButton->OnClicked.AddUniqueDynamic(gameMode, &ADungeonGameMode::GoToNextStage);
	ReturnButton->OnClicked.AddUniqueDynamic(gameMode, &ADungeonGameMode::GoToLobby);
}
