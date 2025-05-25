// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/InnerIntArray.h"
#include <Engine/DataTable.h>
#include "StageDataRow.generated.h"

struct FInnerIntArray;

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FStageDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StageName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ExpReward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 GoldReward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> ItemReward;

	// TArray<TArray<int32>>, TMap<int32, TArray<int32>> : 이런 형태로 사용 불가
	// 일반적으로 c++에선 사용 가능하지만 구조체 내 UPROPERTY로 선언하는 것이 불가능
	// 언리얼의 리플렉션 시스템에선 지원하지 않음.
	// 배열을 새로운 구조체로 랩핑하는 것으로 우회
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInnerIntArray> EnemyListPerWave;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInnerIntArray> EnemySpawnPerWave;
};
