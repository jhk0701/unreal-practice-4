// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameDatabaseSystem.h"
#include "CommonConst.h"
#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>
#include <Engine/DataTable.h>

#include "TopDownRPG/TopDownRPG.h"


void UGameDatabaseSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadGameDatas();
}

FString EnumToString(ETableType EnumValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETableType"), true);
    if (!EnumPtr)
    {
        return FString("Invalid Enum");
    }
	return EnumPtr->GetDisplayNameTextByIndex((int32)EnumValue).ToString();
}

void UGameDatabaseSystem::LoadGameDatas()
{
	FStreamableManager& stream = UAssetManager::Get().GetStreamableManager();

	// 0. 로드할 에셋들
	int32 cnt = (int32)ETableType::COUNT;
	
	for (int32 i = 0; i < cnt; ++i) 
	{
		ETableType table = (ETableType)(i);

		// 1. 경로에서 에셋 로드
		FSoftObjectPath path(FString::Format(*CommonConst::PATH_FORMAT_DATA_TABLE, { EnumToString(table) }));

		stream.RequestAsyncLoad(
			path, 
			FStreamableDelegate::CreateLambda(
				[this, path, table]()
				{
					// 2. 로드한 에셋 캐싱
					if(UDataTable* loaded = Cast<UDataTable>(path.ResolveObject()))
					{
						this->GameDatabase.Add(table, loaded);
						// PRINT_LOG(TEXT("%s table load completed"), *EnumToString(table));
					}
				}));
	}
}
