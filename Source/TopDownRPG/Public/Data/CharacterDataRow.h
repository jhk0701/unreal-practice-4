// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "TDRPGEnum.h"
#include "CharacterDataRow.generated.h"


USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FCharacterDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ClassName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Desc;

	// Ability 기초값
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EAbility, int32> Ability;

	// Status 기초값
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EStatus, int32> Status;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> SkillID;

};
