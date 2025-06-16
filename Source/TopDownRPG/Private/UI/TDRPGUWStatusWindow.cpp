// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWStatusWindow.h"
#include "Core/PlayerManager.h"

#include "Core/TDRPGGameState.h"
#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>

void UTDRPGUWStatusWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);
}

void UTDRPGUWStatusWindow::Open()
{
	Super::Open();
	Refresh();
}

void UTDRPGUWStatusWindow::Bind(UPlayerManager* InPlayer)
{
	BindedPlayer = InPlayer;
	Refresh();
}

void UTDRPGUWStatusWindow::Refresh()
{
	if (!BindedPlayer)
		return;

	NameLabel->SetText(FText::FromName(BindedPlayer->PlayerData.PlayerName));
	ClassLabel->SetText(FText::FromName(BindedPlayer->ClassName));

	LvLabel->SetText(FText::FromString(FString::Printf(TEXT("Lv. %u"), BindedPlayer->Lv)));

	uint32 CurExp = BindedPlayer->Exp->GetCurrentValue();
	uint32 MaxExp = BindedPlayer->Exp->GetMaxValue();
	float ExpPer = (float)CurExp / MaxExp;
	ExpLabel->SetText(FText::FromString(FString::Printf(TEXT("%0.2f% (%u / %u)"), ExpPer, CurExp, MaxExp)));

	// TODO : 캐릭터 인스턴스 데이터 통합 방법 생각
	ATDRPGGameState* GameState = Cast<ATDRPGGameState>(GetWorld()->GetGameState());
	UCharacterData* CharData = GameState->Player->DataComp;

	uint32 CurHp = CharData->Stat[EStatus::Hp]->GetCurrentValue();
	uint32 MaxHp = CharData->Stat[EStatus::Hp]->GetMaxValue();
	HpLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), CurHp, MaxHp)));

	uint32 CurMp = CharData->Stat[EStatus::Mp]->GetCurrentValue();
	uint32 MaxMp = CharData->Stat[EStatus::Mp]->GetMaxValue();
	MpLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), CurMp, MaxMp)));

	StrLabel->SetText(FText::FromString(FString::FromInt(CharData->Ability[EAbility::Str])));
	DexLabel->SetText(FText::FromString(FString::FromInt(CharData->Ability[EAbility::Dex])));
	IntLabel->SetText(FText::FromString(FString::FromInt(CharData->Ability[EAbility::Int])));
	
	AtkLabel->SetText(FText::FromString(FString::FromInt(CharData->GetAttackPower())));
	DefLabel->SetText(FText::FromString(FString::FromInt(CharData->GetDefensePower())));
}
