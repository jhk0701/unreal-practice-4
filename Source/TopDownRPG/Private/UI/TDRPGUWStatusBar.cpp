// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWStatusBar.h"
#include "Character/TDRPGPlayer.h"
#include "Character/CharacterStatus.h"
#include <Blueprint/WidgetTree.h>
#include <Components/Widget.h>
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>


void UTDRPGUWStatusBar::NativeConstruct()
{
	Super::NativeConstruct();

}


void UTDRPGUWStatusBar::InitStatusBar(TWeakObjectPtr<ATDRPGPlayer> NewPlayer)
{
	player = NewPlayer;
	PlayerNameLabel->SetText(FText::FromString(player->GetActorNameOrLabel()));

	player->statusComp->Stat[EStatus::Hp]->OnValueChanged.AddUObject(this, &UTDRPGUWStatusBar::OnHpChanged);
	player->statusComp->Stat[EStatus::Mp]->OnValueChanged.AddUObject(this, &UTDRPGUWStatusBar::OnMpChanged);
}

void UTDRPGUWStatusBar::OnHpChanged(uint32 Max, uint32 Current)
{
	float percent = Current / (float)Max;

	HealthLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), Current, Max)));
	HealthBar->SetPercent(percent);
}

void UTDRPGUWStatusBar::OnMpChanged(uint32 Max, uint32 Current)
{
	float percent = Current / (float)Max;

	ManaLabel->SetText(FText::FromString(FString::Printf(TEXT("%u / %u"), Current, Max)));
	ManaBar->SetPercent(percent);
}
