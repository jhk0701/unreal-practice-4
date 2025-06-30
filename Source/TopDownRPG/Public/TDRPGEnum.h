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

	COUNT
};


UENUM(BlueprintType)
enum class EStatus : uint8
{
	Hp		UMETA(DisplayName = "Health Point"),
	Mp		UMETA(DisplayName = "Mana Point"),

	Shield	UMETA(DisplayName = "Shield Point"),

	COUNT
};

UENUM(BlueprintType)
enum class EAbility : uint8
{
	Str		UMETA(DisplayName = "Strength"),
	Dex		UMETA(DisplayName = "Dexterity"),
	Int		UMETA(DisplayName = "Intelligence"),
	Vit		UMETA(DisplayName = "Vitality"),
	Foc		UMETA(DisplayName = "Focus"),

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

DECLARE_ENUM_TO_STRING(ERarity);
DECLARE_ENUM_TO_STRING(ETableType);

class FTDRPGEnum 
{
public:
	static FString EnumToString(const ERarity InValue);
	static FString EnumToString(const ETableType InValue);
};
