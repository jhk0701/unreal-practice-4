// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ResourceLoadManager.h"


void UResourceLoadManager::Load(const FSoftObjectPath& InPath, FOnResourceLoaded&& OnCompleteDelegate)
{
	FStreamableManager& Stream = UAssetManager::GetStreamableManager();

	if (UObject* Loaded = InPath.ResolveObject())
	{
		OnCompleteDelegate.ExecuteIfBound(Loaded);
		return;
	}

	Stream.RequestAsyncLoad(InPath,
		FStreamableDelegate::CreateLambda(
			[InPath, OnCompleteDelegate]()
			{
				if (UObject* Loaded = InPath.ResolveObject())
					OnCompleteDelegate.ExecuteIfBound(Loaded);
			}
		)
	);
	
}
