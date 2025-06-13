// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDRPGHUD.h"
#include "Core/UIManager.h"


void ATDRPGHUD::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void ATDRPGHUD::Initialize()
{
	UUIManager* UIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	UIManager->SetHUD(this);

	if (!CommonUI) 
		return;

	UIManager->InitUIConfig(CommonUI);
}
