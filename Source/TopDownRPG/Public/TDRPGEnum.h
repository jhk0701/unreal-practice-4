// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Normal = 0	UMETA(DisplayName = "Normal"),
	Rare		UMETA(DisplayName = "Rare"),
	Heroic		UMETA(DisplayName = "Heroic"),
	Legendary	UMETA(DisplayName = "Legendary"),
	Mythic		UMETA(DisplayName = "Mythic"),
};