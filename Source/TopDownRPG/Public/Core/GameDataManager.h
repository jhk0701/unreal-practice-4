// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonConst.h"
#include "Data/InnerIntArray.h"
#include <Templates/EnableIf.h>
#include <Engine/AssetManager.h>
#include "GameDataManager.generated.h"


UENUM(BlueprintType)
enum class ETableType : uint8
{
	Character,
	Leveling,
	Stage,
	Equipment,
	Consume,
	Ingredient,

	COUNT
};


DECLARE_ENUM_TO_STRING(ETableType);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UGameDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	TMap<ETableType, class UDataTable*> GameDatabase;

	// 레벨링 계산 편의용
	// CharID - Lv : 레벨 범위
	UPROPERTY()
	TMap<FString, FInnerIntArray> LevelRange;


public:
	void LoadGameDatas();

	// 외부에서 특정 테이블에 접근해서 열을 받기 위한 용도
	template<typename T>
	inline TEnableIf<TIsDerivedFrom<T, FTableRowBase>::Value, T*>::type
	GetRow(ETableType Table, const FName& ID)
	{
		return GameDatabase[Table]->FindRow<T>(ID, CommonConst::DATA_TABLE_CONTEXT);
	}

	void GetLeveling(const FString& CharID, const int32 Lv, TArray<int32>& OutLeveling);
	const FString GetLevelingKey(const FString& CharID, const int32 Index);

	UPrimaryDataAsset* LoadPrimaryAssetData(const FPrimaryAssetId& ID);

	const FString EnumToString(ETableType EnumValue);

protected:
	void ProcessLevelData();
};
