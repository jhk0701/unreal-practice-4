// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAbility.h"

#include "TopDownRPG/TopDownRPG.h" // 디버깅


UPlayerAbility::UPlayerAbility()
{
}

void UPlayerAbility::InitAbility(const TArray<uint32>& InitValues)
{
	for (int32 i = 0; i < InitValues.Num(); i++)
	{
		Ability.Add((EAbility)i, InitValues[i]);
	}
}

uint32 UPlayerAbility::GetAttackPower()
{
	return uint32(100);
}

uint32 UPlayerAbility::GetDefensePower()
{
	return uint32(100);
}
