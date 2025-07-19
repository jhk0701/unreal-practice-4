// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAnim.h"
#include "Character/TDRPGPlayer.h"
#include "Character/PlayerAction.h"
#include "Character/CharacterData.h"

#include "TDRPGConst.h"


void UPlayerAnim::SetIsDead(const APawn* Pawn)
{
	if (const ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Pawn))
	{
		bIsDead = Player->GetData()->bIsDead;
	}
}

void UPlayerAnim::PlayAttack(UAnimMontage* InMontage, const FString& InFmt)
{
	if (!InMontage)
		return;

	if (AttackMontage != InMontage)
		AttackMontage = InMontage;

	if (Montage_IsPlaying(AttackMontage))
		return;

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(TryGetPawnOwner()))
		Player->PlayAnimMontage(AttackMontage, 1.0f, FName(InFmt));

}

void UPlayerAnim::PlayAttackLast()
{
	if (!AttackMontage)
		return;

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(TryGetPawnOwner()))
		Player->PlayAnimMontage(AttackMontage, 1.0f, FName(FString::Format(*FTDRPGConst::MONTAGE_FORMAT_ATTACK, { TEXT("Last") })));
}

void UPlayerAnim::PlayHit()
{
	if (Montage_IsPlaying(HitMontage))
		return;

	if(ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(TryGetPawnOwner()))
	{
		int Cnt = HitMontage->GetNumSections();
		int Idx = FMath::RandRange(0, Cnt - 1);

		Player->PlayAnimMontage(HitMontage, 1.0f, FName(FString::Printf(TEXT("Hit_%d"), Idx)));
	}
}

