// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAnim.h"
#include "Character/TDRPGPlayer.h"
#include "Character/PlayerAttack.h"
#include "Character/CharacterData.h"


void UPlayerAnim::SetIsDead(const APawn* Pawn)
{
	if (const ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Pawn))
	{
		bIsDead = Player->GetData()->bIsDead;
	}
}

void UPlayerAnim::PlayAttack(int32 Idx)
{
	if (Montage_IsPlaying(AttackMontage))
		return;

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(TryGetPawnOwner()))
	{
		int Cnt = AttackMontage->GetNumSections();
		Cnt = Cnt == 0 ? 1 : Cnt;
		Player->PlayAnimMontage(AttackMontage, 1.0f, FName(FString::Printf(TEXT("Attack_%d"), Idx % Cnt)));
	}
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

void UPlayerAnim::OnAttackStarted()
{
	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(TryGetPawnOwner()))
		Player->AttackComp->ActivateHitCollider(true);
}

void UPlayerAnim::OnAttackEnded()
{
	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(TryGetPawnOwner()))
		Player->AttackComp->ActivateHitCollider(false);
}
