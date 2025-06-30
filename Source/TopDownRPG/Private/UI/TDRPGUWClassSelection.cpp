// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWClassSelection.h"
#include "InGame/Title/TitleGameState.h"
#include "UI/Element/TDRPGUWButton.h"

#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/CharacterDataRow.h"

#include <Components/VerticalBox.h>
#include <Components/TextBlock.h>


void UTDRPGUWClassSelection::InitClassList()
{
	// 캐릭터 정보 리스트에서 정보 출력
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	TArray<FString> CharIDs;
	GameData->GetPlayableCharIDs(CharIDs);

	for (auto& CharID : CharIDs)
	{
		UTDRPGUWButton* Button = CreateWidget<UTDRPGUWButton>(this, ButtonFactory);
		
		ClassList->AddChild(Button);
		
		FCharacterDataRow* Data = GameData->GetRow<FCharacterDataRow>(ETableType::Character, CharID);
		Button->SetLabel(FText::FromName(Data->ClassName));
		Button->ButtonAction.AddLambda([this, CharID]() { this->SelectClass(CharID); });
	}

	SelectClass(CharIDs[0]); // 첫번째 클래스 선택
}

void UTDRPGUWClassSelection::SelectClass(const FString& InCharID)
{
	ATitleGameState* State = Cast<ATitleGameState>(GetWorld()->GetGameState());
	State->NewCharID = InCharID;

	ShowCharData(InCharID);
}

void UTDRPGUWClassSelection::ShowCharData(const FString& InCharID)
{
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FCharacterDataRow* CharData = GameData->GetRow<FCharacterDataRow>(ETableType::Character, InCharID);

	ClassLabel->SetText(FText::FromName(CharData->ClassName));
	ClassDescLabel->SetText(FText::FromString(CharData->Desc));
}
