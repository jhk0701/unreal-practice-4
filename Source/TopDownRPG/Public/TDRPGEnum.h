// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETableType : uint8
{
	Character,
	Leveling,
	Stage,

	// Item
	Weapon,
	Equipment,
	Consume,
	Ingredient,

	// 
	Merchant,
	Skill,

	COUNT
};


UENUM(BlueprintType)
enum class EStatus : uint8
{
	Hp		UMETA(DisplayName = "Health Point"),
	Mp		UMETA(DisplayName = "Mana Point"),

	COUNT
};

UENUM(BlueprintType)
enum class EAbility : uint8
{
	Str		UMETA(DisplayName = "STR"),
	Dex		UMETA(DisplayName = "DEX"),
	Int		UMETA(DisplayName = "INT"),
	Foc		UMETA(DisplayName = "FOC"),
	// Vit		UMETA(DisplayName = "VIT"),

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

	COUNT
};

UENUM(BlueprintType)
enum class EOperateType : uint8
{
	Addictive,
	Multiply,
	Override,
};

UENUM(BlueprintType)
enum class ESkillInput : uint8 
{
	Normal,
	Combo,
	Casting,
	Charging,
	Area,
};

DECLARE_ENUM_TO_STRING(ERarity);
DECLARE_ENUM_TO_STRING(ETableType);
DECLARE_ENUM_TO_STRING(EStatus);
DECLARE_ENUM_TO_STRING(EAbility);

class FTDRPGEnum 
{
public:
	static FString EnumToString(const ERarity InValue);
	static FString EnumToString(const ETableType InValue);
	static FString EnumToString(const EStatus InValue);
	static FString EnumToString(const EAbility InValue);
};
