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
	FVector velocity = Pawn->GetVelocity().GetSafeNormal();
	FVector forward = Pawn->GetActorForwardVector();

	double dir = FVector::DotProduct(velocity, forward);
	Accel = (float)FMath::Max(dir, 0) * AccelScaler;
}

void UCharacterAnimBase::SetIsDead(const APawn* Pawn)
{
	bIsDead = false;
}

void UCharacterAnimBase::PlayAttack(const int32 Idx)
{
	Montage_Play(attackMontage);
}

void UCharacterAnimBase::PlayHit()
{
	Montage_Play(hitMontage);
}
