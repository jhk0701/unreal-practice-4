// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "LevelingDataRow.generated.h"


USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FLevelingDataRow : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Str;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Dex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Int;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Hp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Mp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ExpDemand;
};
