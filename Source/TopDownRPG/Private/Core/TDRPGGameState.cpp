// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDRPGGameState.h"

#include "Core/PlayerDataManager.h"
#include "Core/PlayerManager.h"

void ATDRPGGameState::Save()
{
	UGameInstance* GameInst = GetGameInstance();
	UPlayerDataManager* PlayerData = GameInst->GetSubsystem<UPlayerDataManager>();
	PlayerData->SaveData(GameInst->GetSubsystem<UPlayerManager>());
}
