// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDRPGInstance.h"

#include "Core/GameDataManager.h"
#include "Core/PlayerManager.h"

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGInstance::Init()
{
	Super::Init();

	UGameDataManager* GameData = GetSubsystem<UGameDataManager>();
	GameData->LoadGameDatas();

	UPlayerManager* Player = GetSubsystem<UPlayerManager>();
	Player->LoadData();
}
