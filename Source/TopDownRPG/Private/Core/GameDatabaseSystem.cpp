// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameDatabaseSystem.h"
#include "Data/LevelingDataRow.h"
#include "CommonConst.h"
#include <Engine/DataTable.h>

#include "TopDownRPG/TopDownRPG.h"


void UGameDatabaseSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 게임 데이터 준비
	// 데이터 테이블 로드
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

		// 비동기 방식 -> 동기 방식으로 변경
		auto handle = stream.RequestSyncLoad(path);

		// 2. 로드한 에셋 캐싱
		if (UDataTable* loaded = Cast<UDataTable>(path.ResolveObject()))
			GameDatabase.Add(table, loaded);
	}

	// 로드한 데이터 후처리
	ProcessLevelData();
}

void UGameDatabaseSystem::ProcessLevelData()
{
	TArray<FName> keys = GameDatabase[ETableType::Leveling]->GetRowNames();

	for (int32 i = 0; i < keys.Num(); ++i)
	{
		// id 분리
		FString fullID = keys[i].ToString();
		FString charID = fullID.Left(4);	// 앞에 4글자 : 캐릭터 ID
		FString lv = fullID.Right(3);		// 뒤에 3글자 : 레벨

		if (!LevelRange.Contains(charID))
			LevelRange.Add(charID);

		LevelRange[charID].Array.Add(FCString::Atoi(*lv));
	}
}

void UGameDatabaseSystem::GetLeveling(const FString& CharID, const int32 Lv, TArray<int32>& OutLeveling)
{
	// 초기화
	OutLeveling.Empty(); // 이 배열을 가지고 외부에서 스펙을 더한다.

	if (!LevelRange.Contains(CharID))
		return;

	// 현재 레벨이 어느 레벨 구간에 속하는지 구한다.
	for (int32 i = 0; i < LevelRange[CharID].Array.Num(); i++)
	{
		if (LevelRange[CharID].Array[i] >= Lv)
		{
			// 해당 레벨 구간 - 현재 레벨 갯수를 배열에 넣는다.
			int32 size = LevelRange[CharID].Array[i] - Lv;
			OutLeveling.Add(size);
			break;
		}
		else 
		{
			// 이전 레벨 구간을 레벨링 배열에 넣는다
			int32 size = LevelRange[CharID].Array[i + 1] - LevelRange[CharID].Array[i];
			OutLeveling.Add(size);
		}
	}
}

const FString UGameDatabaseSystem::GetLevelingKey(const FString& CharID, const int32 Index)
{
	int32 range = LevelRange[CharID].Array[Index];
	return CharID + FString::Printf(TEXT("%03d"), range);
}

UPrimaryDataAsset* UGameDatabaseSystem::LoadPrimaryAssetData(const FPrimaryAssetId& ID)
{
	UAssetManager& Manager = UAssetManager::Get();

	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(ID));

	if (AssetPtr.IsPending())
		AssetPtr.LoadSynchronous();

	return Cast<UPrimaryDataAsset>(AssetPtr.Get());
}
