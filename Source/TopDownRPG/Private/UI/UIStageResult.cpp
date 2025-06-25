// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIStageResult.h"
#include "InGame/Dungeon/DungeonGameMode.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>


void UUIStageResult::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindButton();
}

void UUIStageResult::SetResult(bool bIsCleared)
{
	ResultLabel->SetText(bIsCleared ? FText::FromString(TEXT("Stage Cleared")) : FText::FromString(TEXT("Stage Failed")));
}

void UUIStageResult::BindButton()
{
	ADungeonGameMode* gameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());

	if (!gameMode)
		return;

	NextButton->OnClicked.AddUniqueDynamic(gameMode, &ADungeonGameMode::GoToNextStage);
	ReturnButton->OnClicked.AddUniqueDynamic(gameMode, &ADungeonGameMode::GoToLobby);
}
