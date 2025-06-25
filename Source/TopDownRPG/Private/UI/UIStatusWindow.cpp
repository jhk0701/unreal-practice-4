// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIStatusWindow.h"

#include "TDRPGEnum.h"
#include "Core/PlayerManager.h"
#include "Core/TDRPGGameState.h"
#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>

void UUIStatusWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UUIBase::Close);
}

void UUIStatusWindow::Open()
{
	Super::Open();
	Refresh();
}

void UUIStatusWindow::Bind(UPlayerManager* InPlayer)
{
	BindedPlayer = InPlayer;
	Refresh();
}

void UUIStatusWindow::Refresh()
{
	if (!BindedPlayer)
		return;

	NameLabel->SetText(FText::FromName(BindedPlayer->PlayerData->PlayerName));
	ClassLabel->SetText(FText::FromName(BindedPlayer->ClassName));

	LvLabel->SetText(FText::FromString(FString::Printf(TEXT("Lv. %u"), BindedPlayer->Lv)));

	uint32 CurExp = BindedPlayer->Exp->GetCurrentValue();
	uint32 MaxExp = BindedPlayer->Exp->GetMaxValue();
	float ExpPer = (float)CurExp / MaxExp;
	ExpLabel->SetText(FText::FromString(FString::Printf(TEXT("%0.2f %% (%u / %u)"), ExpPer, CurExp, MaxExp)));

	// TODO : 캐릭터 인스턴스 데이터 통합 방법 생각
	ATDRPGGameState* GameState = Cast<ATDRPGGameState>(GetWorld()->GetGameState());
	UCharacterData* CharData = GameState->Player->DataComp;
	
	FText ContentText;
	GetStatusText(CharData, EStatus::Hp, ContentText);
	HpLabel->SetText(ContentText);
	GetStatusText(CharData, EStatus::Mp, ContentText);
	MpLabel->SetText(ContentText);

	GetAbilityText(CharData, EAbility::Str, ContentText);
	StrLabel->SetText(ContentText);
	GetAbilityText(CharData, EAbility::Dex, ContentText);
	DexLabel->SetText(ContentText);
	GetAbilityText(CharData, EAbility::Int, ContentText);
	IntLabel->SetText(ContentText);
	
	AtkLabel->SetText(FText::FromString(FString::FromInt(CharData->GetAttackPower())));
	DefLabel->SetText(FText::FromString(FString::FromInt(CharData->GetDefensePower())));
}

void UUIStatusWindow::GetStatusText(UCharacterData* InCharData, EStatus InType, FText& OutText)
{
	uint32 CurHp = InCharData->Stat[InType]->GetCurrentValue();
	uint32 MaxHp = InCharData->Stat[InType]->GetMaxValue();

	OutText = FText::FromString(FString::Printf(TEXT("%u / %u"), CurHp, MaxHp));
}

void UUIStatusWindow::GetAbilityText(UCharacterData* InCharData, EAbility InType, FText& OutText)
{
	uint32 Base = InCharData->BaseAbility[InType];
	uint32 Equip = InCharData->EquipmentAbility[InType];
	uint32 Total = Base + Equip;

	OutText = FText::FromString(FString::Printf(TEXT("%u (%u + %u)"), Total, Base, Equip));
}
