// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/RecoveryFunc.h"

#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include "Character/Status.h"

void URecoveryFunc::Activate(AActor* InTarget, uint32 InValue)
{
	Super::Activate(InTarget, InValue);

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(InTarget))
		Player->DataComp->Stat[TargetToRecover]->Add(InValue);
}
