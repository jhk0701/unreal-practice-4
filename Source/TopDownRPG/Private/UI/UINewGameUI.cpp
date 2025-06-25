// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UINewGameUI.h"
#include "InGame/Title/TitleGameMode.h"
#include "InGame/Title/TitleGameState.h"

#include "UI/UIClassSelection.h"
#include "UI/UIInputPlayerName.h"

#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/EditableTextBox.h>


void UUINewGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UUIBase::Close);

	ClassSelectionPage->NextButton->OnClicked.AddUniqueDynamic(this, &UUINewGameUI::OpenInputNamePage);
	InputPlayerNamePage->BackButton->OnClicked.AddUniqueDynamic(this, &UUINewGameUI::OpenClassSelectPage);
	InputPlayerNamePage->CompleteButton->OnClicked.AddUniqueDynamic(this, &UUINewGameUI::Complete);

	ClassSelectionPage->InitClassList();
}

void UUINewGameUI::OpenClassSelectPage()
{
	BodySwitcher->SetActiveWidgetIndex(0);
}

void UUINewGameUI::OpenInputNamePage()
{
	BodySwitcher->SetActiveWidgetIndex(1);
}

void UUINewGameUI::Complete()
{
	ATitleGameState* State = Cast<ATitleGameState>(GetWorld()->GetGameState());
	if (State)
		State->NewPlayerName = InputPlayerNamePage->NameInputField->GetText().ToString();

	ATitleGameMode* Mode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());

	if (State && Mode)
		Mode->CreateNewGameData(State->NewClassID, State->NewPlayerName);
	
}
