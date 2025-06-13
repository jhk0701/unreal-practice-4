// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TDRPGHUD.h"
#include "Core/UIManager.h"


void ATDRPGHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitHUD();
}

void ATDRPGHUD::InitHUD()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance) 
		return;

	UUIManager* UIManager = GameInstance->GetSubsystem<UUIManager>();
	UIManager->SetHUD(this);

	UIManager->InitUIConfig(CommonUI);

	for (auto Config : Configs) 
		UIManager->InitUIConfig(Config);
}
