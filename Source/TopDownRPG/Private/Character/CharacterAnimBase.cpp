#include "Character/CharacterAnimBase.h"


void UCharacterAnimBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AccelScaler = 500.f;
	Accel = 0.0f;
}

void UCharacterAnimBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(APawn* pawn = TryGetPawnOwner())
	{
		SetAccel(pawn);
		SetIsDead(pawn);
	}
}

void UCharacterAnimBase::SetAccel(const APawn* Pawn)
{
	FVector Velocity = Pawn->GetVelocity().GetSafeNormal();
	FVector Forward = Pawn->GetActorForwardVector();

	double Dir = FVector::DotProduct(Velocity, Forward);
	Accel = (float)FMath::Max(Dir, 0) * AccelScaler;
}

void UCharacterAnimBase::SetIsDead(const APawn* Pawn)
{
	bIsDead = false;
}

void UCharacterAnimBase::PlayAttack(const int32 Idx)
{
	Montage_Play(AttackMontage);
}

void UCharacterAnimBase::PlayHit()
{
	Montage_Play(HitMontage);
}
