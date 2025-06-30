// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "TDRPGEnum.h"
#include "LevelingDataRow.generated.h"


USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FLevelingDataRow : public FTableRowBase
{
	GENERATED_BODY();

public:

	// Ability 기초값
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EAbility, int32> Ability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EStatus, int32> Status;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ExpDemand;
};
