// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>
#include "ResourceLoadManager.generated.h"

DECLARE_DELEGATE_OneParam(FOnResourceLoaded, UObject*);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UResourceLoadManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Load(FSoftObjectPath& InPath, FOnResourceLoaded&& OnCompleteDelegate);
	
	template<typename T>
	void Load(TSoftObjectPtr<T>& InSoft)
	{
		FStreamableManager& Stream = UAssetManager::GetStreamableManager();
		Stream.RequestAsyncLoad(InSoft.ToSoftObjectPath());
	};

	template<typename T>
	void LoadTask(TSoftObjectPtr<T>& InSoft, FOnResourceLoaded&& OnCompleteDelegate)
	{
		if (InSoft.IsValid())
		{
			OnCompleteDelegate.ExecuteIfBound(InSoft.Get());
			return;
		}

		AsyncTask(ENamedThreads::GameThread, 
			[InSoft, OnCompleteDelegate]()
			{
				T* Loaded = InSoft.LoadSynchronous();

				if (Loaded)
					OnCompleteDelegate.ExecuteIfBound(Loaded);
			}
		);

	};
};
