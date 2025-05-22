// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Core/AssetLoadSubsystem.h"
#include "TopDownRPG/TopDownRPG.h"
#include "UI/TDRPGUserWidget.h"
#include <Templates/EnableIf.h>
#include "UISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FString basePath = TEXT("/Game/4-UI/WBP_%s.WBP_%s_C");

	TMap<FName, class UTDRPGUserWidget*> uiMap;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	template<typename T>
	inline typename TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, T*>::type
	CreateUI()
	{
		PRINT_LOG(TEXT("Create UI"));

		UClass* widgetClass = T::StaticClass();
		if (widgetClass)
		{
			FName name = widgetClass->GetFName();
			FString path = FString::Printf(basePath, *name.ToString(), *name.ToString());
			UAssetLoadSubsystem* assetLoad = GetGameInstance()->GetSubsystem<UAssetLoadSubsystem>();
			T* loaded = assetLoad->Load<T>(path);

			if (!loaded)
				return nullptr;

			uiMap.Add(name, loaded);

			return (T*)loaded;
		}
		else
			return nullptr;
	};

	template<typename T>
	inline typename TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, T*>::type
	GetUI() 
	{
		PRINT_LOG(TEXT("Create UI"));

		FName name = T::StaticClass()->GetFName();
		if (uiMap.Contains(name) && !uiMap[name])
			return (T*)uiMap[name];

		return CreateUI<T>();
	};
};
