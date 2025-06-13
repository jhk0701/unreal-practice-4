// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Title/TitleHUD.h"

#include "Core/UIManager.h"
#include "UI/TDRPGUWTitle.h"

void ATitleHUD::Initialize()
{
	Super::Initialize();

	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();

	if (UTDRPGUWTitle* Title = UI->GetUI<UTDRPGUWTitle>())
		Title->Open();
}
