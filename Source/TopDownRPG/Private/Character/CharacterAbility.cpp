// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAbility.h"

#include "TopDownRPG/TopDownRPG.h" // 디버깅


UCharacterAbility::UCharacterAbility()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAbility::InitAbility(const TArray<uint32>& InitValues)
{
	for (int32 i = 0; i < InitValues.Num(); i++)
	{
		Ability.Add((EAbility)i, InitValues[i]);
	}
}

uint32 UCharacterAbility::GetAttackPower()
{
	return Ability[EAbility::Str];
}

uint32 UCharacterAbility::GetDefensePower()
{
	return uint32(10);
}
