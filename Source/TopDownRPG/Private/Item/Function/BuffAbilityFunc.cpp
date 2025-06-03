// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/BuffAbilityFunc.h"

#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"

void UBuffAbilityFunc::Activate(AActor* InTarget, uint32 InValue)
{
	Super::Activate(InTarget, InValue);

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(InTarget))
		Player->DataComp->Ability[TargetAbility] += InValue;
}

void UBuffAbilityFunc::Deactivate(AActor* InTarget, uint32 InValue)
{
	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(InTarget))
		Player->DataComp->Ability[TargetAbility] -= InValue;
}
