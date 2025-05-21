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

template<class T>
T* UUISubsystem::CreateUI()
{
	PRINT_LOG(TEXT("Create UI"));

	if (T::StaticClass())
	{
		FName name = T::StaticClass()->GetFName();
		FString path = FString::Printf(basePath, *name, *name);

		UAssetLoadSubsystem* assetLoad = GetGameInstance()->GetSubsystem<UAssetLoadSubsystem>();
		T* loaded = assetLoad->Load<T>(path);
		
		if (!loaded)
			return nullptr;

		uiMap.Add(name, loaded);

		return loaded;
	}
	else
		return nullptr;
}

template<typename T>
T* UUISubsystem::GetUI()
{
	PRINT_LOG(TEXT("Create UI"));

	FName name = T::StaticClass()->GetFName();
	if (uiMap.Contains(name) && !uiMap[name])
		return uiMap[name];

	return CreateUI<T>();
}
