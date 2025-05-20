// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAnim.h"
#include "Character/TDRPGPlayer.h"
#include "Character/CharacterStatus.h"

void UPlayerAnim::SetIsDead(const APawn* Pawn)
{
	if (const ATDRPGPlayer* player = Cast<ATDRPGPlayer>(Pawn))
	{
		bIsDead = player->GetStatus()->bIsDead;
	}
}

void UPlayerAnim::PlayAttack(int32 Idx)
{
}

void UPlayerAnim::PlayHit()
{
	if(ATDRPGPlayer* player = Cast<ATDRPGPlayer>(TryGetPawnOwner()))
	{
		int cnt = hitMontage->GetNumSections();
		int idx = FMath::RandRange(0, cnt - 1);

		player->PlayAnimMontage(hitMontage, 1.0f, FName(FString::Printf(TEXT("Hit_%d"), idx)));
	}
}
