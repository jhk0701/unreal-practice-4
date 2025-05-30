// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWTitle.h"
#include "InGame/Title/TitleGameMode.h"
#include <Components/Button.h>

void UTDRPGUWTitle::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindButton();
}

void UTDRPGUWTitle::BindButton()
{
	// Exit
	ATitleGameMode* gameMode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());

	if (!gameMode)
		return;

	NewGameButton->OnClicked.AddUniqueDynamic(gameMode, &ATitleGameMode::StartNewGame);
	ContinueButton->OnClicked.AddUniqueDynamic(gameMode, &ATitleGameMode::ContinueGame);
	ExitButton->OnClicked.AddUniqueDynamic(gameMode, &ATitleGameMode::ExitGame);
}
