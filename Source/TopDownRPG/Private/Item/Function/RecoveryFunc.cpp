// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/RecoveryFunc.h"

#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include "Character/Status.h"

#include "TopDownRPG/TopDownRPG.h"

void URecoveryFunc::Operate(AActor* Object, uint32 Value)
{
	Super::Operate(Object, Value);

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Object))
		Player->DataComp->Stat[TargetToRecover]->Add(Value);

	PRINT_LOG(TEXT("Recover Func"));
}

uint32 URecoveryFunc::Operate(uint32 Object, uint32 Value)
{
	return 0;
}
