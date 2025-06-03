// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/BuffStatusFunc.h"

#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include "Character/Status.h"

void UBuffStatusFunc::Activate(AActor* InTarget, uint32 InValue)
{
	Super::Activate(InTarget, InValue);

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(InTarget))
	{
		switch (OperType)
		{
		case EOperateType::Addictive:
			Player->DataComp->AddictiveStat[TargetStatus] += InValue;
			break;
		case EOperateType::Multiply:
			break;
		case EOperateType::Override:
			break;
		default:
			break;
		}
	}
}

void UBuffStatusFunc::Deactivate(AActor* InTarget, uint32 InValue)
{
	Super::Activate(InTarget, InValue);

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(InTarget))
		Player->DataComp->Stat[TargetStatus]->Subtract(InValue);
}
