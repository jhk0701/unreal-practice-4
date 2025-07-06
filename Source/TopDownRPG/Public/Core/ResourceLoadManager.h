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
	void Load(const FSoftObjectPath& InPath, FOnResourceLoaded&& OnCompleteDelegate);
	
	/*
	template<typename T>
	void Load(TSoftObjectPtr<T>& InSoft, FOnResourceLoaded&& OnCompleteDelegate)
	{
		FStreamableManager& Stream = UAssetManager::GetStreamableManager();
		auto& Path = InSoft.ToSoftObjectPath();

		if (Path.IsValid())
		{
			OnCompleteDelegate.ExecuteIfBound(Path.ResolveObject());
			return;
		}

		Stream.RequestAsyncLoad(
			Path, 
			FStreamableDelegate::CreateLambda(
				[Path, &OnCompleteDelegate]()
				{
					UObject* Loaded = Path.ResolveObject();
					check(Loaded);

					OnCompleteDelegate.ExecuteIfBound(Loaded);
				}
			)
		);
	};

	template<typename T>
	void Load(TSoftClassPtr<T>& InSoft, FOnResourceLoaded&& OnCompleteDelegate)
	{
		FStreamableManager& Stream = UAssetManager::GetStreamableManager();
		
		if (UObject* Loaded = InSoft.Get())
		{
			OnCompleteDelegate.ExecuteIfBound(Loaded);
			return;
		}

		Stream.RequestAsyncLoad(
			InSoft.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[InSoft, &OnCompleteDelegate]()
				{
					UObject* Loaded = InSoft.Get();
					check(Loaded);

					OnCompleteDelegate.ExecuteIfBound(Loaded);
				}
			)
		);
	};
	*/
};
