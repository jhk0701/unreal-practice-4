#include "Character/CharacterAnimBase.h"
#include "TopDownRPG/TopDownRPG.h"



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
	}
}

void UCharacterAnimBase::SetAccel(const APawn* Pawn)
{
	FVector velocity = Pawn->GetVelocity().GetSafeNormal();
	FVector forward = Pawn->GetActorForwardVector();

	double dir = FVector::DotProduct(velocity, forward);
	Accel = (float)FMath::Max(dir, 0) * AccelScaler;
	
	// PRINT_LOG(TEXT("Dir : %g, Accel : %f, AccelScaler : %f"), dir, Accel, AccelScaler);
	// PRINT_LOG(TEXT("Velocity : %s, Forward : %s"), *velocity.ToString(), *forward.ToString());
}
