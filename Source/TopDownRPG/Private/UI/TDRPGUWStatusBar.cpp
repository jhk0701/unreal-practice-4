// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWStatusBar.h"
#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>


void UTDRPGUWStatusBar::InitStatusBar(ATDRPGPlayer* NewPlayer)
{
	player = NewPlayer;
	PlayerNameLabel->SetText(FText::FromString(player->GetActorNameOrLabel()));

	UCharacterData* data = player->dataComp;
	
	data->Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UTDRPGUWStatusBar::OnHpChanged);
	data->Stat[EStatus::Mp]->OnValueChanged.AddUObject(this, &UTDRPGUWStatusBar::OnMpChanged);

	OnHpChanged(data->Stat[EStatus::Hp]->GetMaxValue(), data->Stat[EStatus::Hp]->GetCurrentValue());
	OnMpChanged(data->Stat[EStatus::Mp]->GetMaxValue(), data->Stat[EStatus::Mp]->GetCurrentValue());
}

void UTDRPGUWStatusBar::OnHpChanged(uint32 Max, uint32 Current)
{
	float percent = Current > 0 ? Current / (float)Max : 0;

	HealthLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), Current, Max)));
	HealthBar->SetPercent(percent);
}

void UTDRPGUWStatusBar::OnMpChanged(uint32 Max, uint32 Current)
{
	float percent = Current > 0 ? Current / (float)Max : 0;

	ManaLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), Current, Max)));
	ManaBar->SetPercent(percent);
}
