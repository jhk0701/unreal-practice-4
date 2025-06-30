// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWNewGameUI.h"
#include "InGame/Title/TitleGameMode.h"
#include "InGame/Title/TitleGameState.h"

#include "UI/TDRPGUWClassSelection.h"
#include "UI/TDRPGUWInputPlayerName.h"

#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/EditableTextBox.h>


void UTDRPGUWNewGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);

	ClassSelectionPage->NextButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWNewGameUI::OpenInputNamePage);
	InputPlayerNamePage->BackButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWNewGameUI::OpenClassSelectPage);
	InputPlayerNamePage->CompleteButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWNewGameUI::Complete);

	ClassSelectionPage->InitClassList();
}

void UTDRPGUWNewGameUI::OpenClassSelectPage()
{
	BodySwitcher->SetActiveWidgetIndex(0);
}

void UTDRPGUWNewGameUI::OpenInputNamePage()
{
	BodySwitcher->SetActiveWidgetIndex(1);
}

void UTDRPGUWNewGameUI::Complete()
{
	ATitleGameState* State = Cast<ATitleGameState>(GetWorld()->GetGameState());
	if (State)
		State->NewPlayerName = InputPlayerNamePage->NameInputField->GetText().ToString();

	ATitleGameMode* Mode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());

	if (State && Mode)
		Mode->CreateNewGameData(State->NewCharID, State->NewPlayerName);
	
}
