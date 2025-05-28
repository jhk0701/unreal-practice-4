// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonConst.h"
#include "Data/InnerIntArray.h"
#include <Templates/EnableIf.h>
#include "GameDatabaseSystem.generated.h"


UENUM(BlueprintType)
enum class ETableType : uint8
{
	Character = 0,
	Leveling,

	COUNT
};


DECLARE_ENUM_TO_STRING(ETableType);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UGameDatabaseSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	TObjectPtr<class UInitConfig> InitConfig;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	TMap<ETableType, class UDataTable*> GameDatabase;

	// 레벨링 계산 편의용
	// CharID - Lv : 레벨 범위
	UPROPERTY()
	TMap<FString, FInnerIntArray> LevelRange;


public:
	// 외부에서 특정 테이블에 접근해서 열을 받기 위한 용도
	template<typename T>
	inline TEnableIf<TIsDerivedFrom<T, FTableRowBase>::Value, T*>::type
	GetRow(ETableType Table, const FName& ID)
	{
		return GameDatabase[Table]->FindRow<T>(ID, CommonConst::DATA_TABLE_CONTEXT);
	}

	void GetLeveling(const FString& CharID, const int32 Lv, TArray<int32>& OutLeveling);
	const FString GetLevelingKey(const FString& CharID, const int32 Index);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void LoadGameDatas();

	// Data Table
	void ProcessLevelData();

	// Primary Data Asset
	void InitConfigs();
	void LoadConfigs();

};
