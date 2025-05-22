// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TitleHUD.h"
#include "Core/UISubsystem.h"
#include "UI/TDRPGUWTitle.h"

#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>
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
	FStreamableManager& stream = UAssetManager::GetStreamableManager();

	// FSoftObjectPath 클래스이기 떄문에 클래스로 받아야함
	FSoftClassPath TitleUIPath(TEXT("/Game/4-UI/WBP_TDRPGUWTitle.WBP_TDRPGUWTitle_C"));

	stream.RequestAsyncLoad(TitleUIPath, FStreamableDelegate::CreateLambda([TitleUIPath, this]() 
		{
			/*
			UTDRPGUWTitle* titleUI = Cast<UTDRPGUWTitle>(TitleUIPath.ResolveObject());
			
			if (titleUI)
				titleUI->AddToViewport();
			else
			{
				PRINT_LOG(TEXT("Failed to load"));
			}
			*/

			UClass* widgetClass = Cast<UClass>(TitleUIPath.ResolveObject());
			if (widgetClass)
			{
				UUserWidget* Widget = CreateWidget<UUserWidget>(this->GetWorld(), widgetClass);
				Widget->AddToViewport();
			}
		}));

}
