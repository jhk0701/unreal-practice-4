// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWTitle.h"
#include "InGame/Title/TitleGameMode.h"
#include "Core/PlayerDataManager.h"

#include <Components/Button.h>

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWTitle::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitButton();
}


void UTDRPGUWTitle::InitButton()
{
	UPlayerDataManager* PlayerData = GetGameInstance()->GetSubsystem<UPlayerDataManager>();
	bool bExistSaveData = PlayerData->GetPlayerData().Num() > 0;
	
	ATitleGameMode* GameMode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());

	NewGameButton->OnClicked.AddUniqueDynamic(GameMode, &ATitleGameMode::StartNewGame);
	
	ContinueButton->SetVisibility(bExistSaveData ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (bExistSaveData)
		ContinueButton->OnClicked.AddUniqueDynamic(GameMode, &ATitleGameMode::ContinueGame);
	
	ExitButton->OnClicked.AddUniqueDynamic(GameMode, &ATitleGameMode::ExitGame);
}
