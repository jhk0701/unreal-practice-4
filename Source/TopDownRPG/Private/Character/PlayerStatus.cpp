// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PlayerStatus.h"
#include "Character/Status.h"
#include "TopDownRPG/TopDownRPG.h"

UPlayerStatus::UPlayerStatus()
{
}

void UPlayerStatus::InitStatus(const TArray<EStatus>& StatusType, const TArray<uint32>& InitVal)
{
	if (StatusType.Num() != InitVal.Num())
		return;

	for (int32 i = 0; i < StatusType.Num(); ++i)
	{
		Stat.Add(StatusType[i], MakeUnique<Status>(InitVal[i]));
	}

}
