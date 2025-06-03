// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EStatus : uint8
{
	Hp UMETA(DisplayName = "Health Point"),
	Mp UMETA(DisplayName = "Mana Point"),

	COUNT
};

UENUM(BlueprintType)
enum class EAbility : uint8
{
	Str UMETA(DisplayName = "Strength"),
	Dex UMETA(DisplayName = "Dexterity"),
	Int UMETA(DisplayName = "Intelligence"),

	COUNT
};

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Normal,
	Rare,
	Heroic,
	Legendary,
	Mythic,
};

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Weapon,
	Head,
	Top,
	Bottom,
	Glove,
	Shoes,
};

UENUM(BlueprintType)
enum class EConsumeType : uint8
{
	RecoverHP,
	RecoverMP,
	BuffHP,
	BuffMP,
	BuffStr,
	BuffDex,
	BuffInt,
};