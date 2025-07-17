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

	COUNT	UMETA(Hidden)
};


UENUM(BlueprintType)
enum class EStatus : uint8
{
	Hp		UMETA(DisplayName = "Health Point"),
	Mp		UMETA(DisplayName = "Mana Point"),

	COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAbility : uint8
{
	Str		UMETA(DisplayName = "STR"),
	Dex		UMETA(DisplayName = "DEX"),
	Int		UMETA(DisplayName = "INT"),
	Foc		UMETA(DisplayName = "FOC"),
	// Vit		UMETA(DisplayName = "VIT"),

	COUNT	UMETA(Hidden)
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

	COUNT	UMETA(Hidden)
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
	Holding,
	Charging,
	Casting,
	Area,
};

UENUM(BlueprintType)
enum class ESkillInputKey : uint8
{
	// 스킬
	KeyQ	UMETA(DisplayName = "Q"),
	KeyW	UMETA(DisplayName = "W"),
	KeyE	UMETA(DisplayName = "E"),
	KeyR	UMETA(DisplayName = "R"),
	KeyA	UMETA(DisplayName = "A"),
	KeyS	UMETA(DisplayName = "S"),
	KeyD	UMETA(DisplayName = "D"),
	KeyF	UMETA(DisplayName = "F"),

	COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EInputProcedure : uint8
{
	Ready,
	InProgress,
	Complete
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Active,
	Passive
};

UENUM(BlueprintType)
enum class ESkillDirection: uint8
{
	Forward,
	AllDirection,
};

UENUM(BlueprintType)
enum class EUILayer :uint8
{
	Basic = 0,	// 기본 UI, HUD 형태 배치
	PopUp,		// 팝업 UI 배치
	Top,		// 최상단, 로딩 UI 등등 화면을 가려야하는 UI 배치

	COUNT	UMETA(Hidden)
};


DECLARE_ENUM_TO_STRING(ERarity);
DECLARE_ENUM_TO_STRING(ETableType);
DECLARE_ENUM_TO_STRING(EStatus);
DECLARE_ENUM_TO_STRING(EAbility);
DECLARE_ENUM_TO_STRING(ESkillType);
DECLARE_ENUM_TO_STRING(ESkillInput);
DECLARE_ENUM_TO_STRING(ESkillInputKey);

class FTDRPGEnum 
{
public:
	static FString EnumToString(const ERarity InValue);
	static FString EnumToString(const ETableType InValue);
	static FString EnumToString(const EStatus InValue);
	static FString EnumToString(const EAbility InValue);
	static FString EnumToString(const ESkillType InValue);
	static FString EnumToString(const ESkillInput InValue);
	static FString EnumToString(const ESkillInputKey InValue);
};
