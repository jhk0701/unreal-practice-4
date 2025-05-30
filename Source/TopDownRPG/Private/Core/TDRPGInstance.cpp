// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDRPGInstance.h"
#include "Core/PlayerManager.h"

#include "TopDownRPG/TopDownRPG.h"



void UTDRPGInstance::Init()
{
	Super::Init();

	UPlayerManager* Player = GetSubsystem<UPlayerManager>();
	Player->LoadData();
}
