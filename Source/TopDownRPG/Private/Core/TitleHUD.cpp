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
	if (titleClass)
	{
		titleInstance = CreateWidget(GetWorld(), titleClass);
		titleInstance->AddToViewport();
	}
}
