// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWTitle.h"
#include "Core/TitleGameMode.h"
#include <Components/Button.h>

void UTDRPGUWTitle::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindButton();
}

void UTDRPGUWTitle::BindButton()
{
	// Exit
	ATitleGameMode* GameMode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());

	if (!GameMode)
		return;

	NewGameButton->OnClicked.AddUniqueDynamic(GameMode, &ATitleGameMode::StartNewGame);
	ContinueButton->OnClicked.AddUniqueDynamic(GameMode, &ATitleGameMode::ContinueGame);
	ExitButton->OnClicked.AddUniqueDynamic(GameMode, &ATitleGameMode::ExitGame);
}
