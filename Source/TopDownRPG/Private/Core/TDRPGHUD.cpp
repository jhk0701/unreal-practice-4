// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TDRPGHUD.h"
#include "Core/UIManager.h"

#include "UI/TDRPGUWCanvas.h"


void ATDRPGHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitHUD();
}

void ATDRPGHUD::InitHUD()
{
	UUIManager* UIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	UIManager->SetHUD(this);
	UIManager->InitCanvas();

	for (auto Config : Configs) 
		UIManager->InitUIConfig(Config);
}
