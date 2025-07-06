// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "SkillDataRow.generated.h"

enum class ESkillType : uint8;
enum class ESkillInput : uint8;
enum class ESkillDirection : uint8;
enum class EStatus : uint8;

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FSkillDataRow : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Desc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDefaultAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillInput InputType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EStatus, int32> Requirement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Cooldown;
};
