// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "SkillDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FSkillDataRow : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> SkillValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MpConsume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cooldown;

	// TODO : 공격 타입
};
