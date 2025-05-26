// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "CharacterDataRow.generated.h"

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FCharacterDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CharName;

	// Ability
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Str;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Dex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Int;

	// Status
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Hp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Mp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> SkillId;
};
