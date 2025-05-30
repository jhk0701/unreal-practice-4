// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TitleHUD.h"
#include "Core/UIManager.h"
#include "UI/TDRPGUWTitle.h"
#include "TopDownRPG/TopDownRPG.h"


ATitleHUD::ATitleHUD()
{
}

void ATitleHUD::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void ATitleHUD::Initialize()
{
	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();
	UI->GetUI<UTDRPGUWTitle>(FOnLoadCompleted::CreateUObject(this, &ATitleHUD::InitTitleUI));
}

void ATitleHUD::InitTitleUI(UTDRPGUserWidget* TitleUI)
{
	if (UTDRPGUWTitle* Title = Cast<UTDRPGUWTitle>(TitleUI)) 
		Title->AddToViewport();
}
