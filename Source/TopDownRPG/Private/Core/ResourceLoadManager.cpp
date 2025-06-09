// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ResourceLoadManager.h"
#include "CommonConst.h"

#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>

#include "TopDownRPG/TopDownRPG.h"


void UResourceLoadManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UResourceLoadManager::Deinitialize()
{
	Super::Deinitialize();
}

void UResourceLoadManager::Load(FSoftObjectPath& InPath, FOnResourceLoaded& OnCompleteDelegate)
{
	FStreamableManager& Stream = UAssetManager::GetStreamableManager();
	Stream.RequestAsyncLoad(InPath,
		FStreamableDelegate::CreateLambda(
			[InPath, OnCompleteDelegate]()
			{
				UObject* Loaded = InPath.ResolveObject();

				if (Loaded)
				{
					OnCompleteDelegate.ExecuteIfBound(Loaded);
				}
			}
		)
	);
}