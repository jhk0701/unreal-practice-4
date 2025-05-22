// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UISubsystem.h"
#include "Core/AssetLoadSubsystem.h"

#include "TopDownRPG/TopDownRPG.h"

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PRINT_LOG(TEXT("UI Subsys init")); // GameInstacne보다 먼저 호출됨
}

void UUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}
