// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerBaseComponent.h"
#include "PlayerAbility.generated.h"

UENUM(BlueprintType)
enum class EAbility : uint8
{
	Str UMETA(DisplayName = "Strength"),
	Dex UMETA(DisplayName = "Dexterity"),
	Int UMETA(DisplayName = "Intelligence"),
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerAbility : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	// 힘, 민첩, 지능
	TMap<EAbility, uint32> Ability;

public:
	UPlayerAbility();

	void InitAbility(const TArray<uint32>& InitValues);
	uint32 GetAttackPower();
	uint32 GetDefensePower();
	
};
