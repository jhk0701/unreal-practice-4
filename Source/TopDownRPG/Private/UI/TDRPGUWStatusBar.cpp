// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWStatusBar.h"
#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"

#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>


void UTDRPGUWStatusBar::InitStatusBar(ATDRPGPlayer* NewPlayer)
{
	Player = NewPlayer;
	PlayerNameLabel->SetText(FText::FromString(Player->GetActorNameOrLabel()));

	UCharacterData* Data = Player->DataComp;
	
	Data->Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UTDRPGUWStatusBar::OnHpChanged);
	Data->Stat[EStatus::Mp]->OnValueChanged.AddUObject(this, &UTDRPGUWStatusBar::OnMpChanged);

	OnHpChanged(Data->Stat[EStatus::Hp]->GetMaxValue(), Data->Stat[EStatus::Hp]->GetCurrentValue());
	OnMpChanged(Data->Stat[EStatus::Mp]->GetMaxValue(), Data->Stat[EStatus::Mp]->GetCurrentValue());
}

void UTDRPGUWStatusBar::OnHpChanged(uint32 Max, uint32 Current)
{
	float Percent = Current > 0 ? Current / (float)Max : 0;

	HealthLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), Current, Max)));
	HealthBar->SetPercent(Percent);
}

void UTDRPGUWStatusBar::OnMpChanged(uint32 Max, uint32 Current)
{
	float Percent = Current > 0 ? Current / (float)Max : 0;

	ManaLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), Current, Max)));
	ManaBar->SetPercent(Percent);
}
