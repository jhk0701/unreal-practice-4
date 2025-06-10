// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
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
	void Load(FSoftObjectPath& InPath, FOnResourceLoaded& OnCompleteDelegate);

	template<typename T>
	void LoadTask(TSoftObjectPtr<T>& InSoft, FOnResourceLoaded& OnCompleteDelegate)
	{
		if (InSoft.IsValid())
		{
			OnCompleteDelegate.ExecuteIfBound(InSoft.Get());
			return;
		}

		UE::Tasks::FTask Task = UE::Tasks::Launch(
			UE_SOURCE_LOCATION, 
			[&]() 
			{
				T* Loaded = InSoft.LoadSynchronous();
				if (Loaded)
					OnCompleteDelegate.ExecuteIfBound(Loaded);
			});

	};
};
