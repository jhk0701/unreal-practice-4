// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TitleHUD.h"
#include "Core/UISubsystem.h"
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
	UUISubsystem* uiSys= GetGameInstance()->GetSubsystem<UUISubsystem>();
	uiSys->GetUI<UTDRPGUWTitle>(FOnLoadCompleted::CreateUObject(this, &ATitleHUD::InitTitleUI));
}

void ATitleHUD::InitTitleUI(UTDRPGUserWidget* TitleUI)
{
	if (UTDRPGUWTitle* title = Cast<UTDRPGUWTitle>(TitleUI)) 
	{
		title->AddToViewport();
	}
}
