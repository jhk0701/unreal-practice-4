// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TitleHUD.h"
#include "Core/UISubsystem.h"
#include "UI/TDRPGUWTitle.h"

#include "TopDownRPG/TopDownRPG.h"

ATitleHUD::ATitleHUD()
{
	// /Script/UMGEditor.WidgetBlueprint''
	basePath = TEXT("");
}

void ATitleHUD::BeginPlay()
{
	Super::BeginPlay();
	// FName name = UTDRPGUWStatusBar::StaticClass()->GetFName();
	// PRINT_LOG(TEXT("call %s"), *name.ToString());

	// FString test = FString::Format(TEXT("/Game/4-UI/WBP_{0}.WBP_{0}_C"), { });
	// FString name = UTDRPGUWStatusBar::StaticClass()->GetFName().ToString();
	// FString text = FString::Printf(TEXT("/Game/4-UI/WBP_%s.WBP_%s_C"), *name, *name);

	// FString text = FString(typeid(UTDRPGUWStatusBar).name());
	Initialize();
}

void ATitleHUD::Initialize()
{
	UUISubsystem* ui = GetGameInstance()->GetSubsystem<UUISubsystem>();
	if (UTDRPGUWTitle* title = ui->GetUI<UTDRPGUWTitle>())
		title->AddToViewport();
	else
		PRINT_LOG(TEXT("HUD Initialize failed"));
}
