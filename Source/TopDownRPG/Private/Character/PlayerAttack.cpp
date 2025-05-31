// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAttack.h"
#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/PlayerAnim.h"
#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"


UPlayerAttack::UPlayerAttack()
{
}

void UPlayerAttack::InitializeComponent()
{
	Super::InitializeComponent();

	Player->HitCollider->OnComponentBeginOverlap.AddDynamic(this, &UPlayerAttack::OnActorOverlaped);
	ActivateHitCollider(false);
}

void UPlayerAttack::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->AttackNormalAction, ETriggerEvent::Triggered, this, &UPlayerAttack::InputAttack);
}

void UPlayerAttack::InputAttack(const FInputActionValue& InputValue)
{
	InvokeAttack();
}

void UPlayerAttack::InvokeAttack()
{
	if (Player->AnimInst->IsAttackPlaying())
		return;

	Player->InvokeAttackDelegate(); // 이동 기능은 꺼질 것
	
	// 커서 방향으로 바라보도록
	FHitResult HitResult;
	Player->GetMouseToWorld(HitResult);

	FVector Dir = HitResult.ImpactPoint - Player->GetActorLocation();
	Player->SetActorRotation(Dir.ToOrientationQuat());

	// 애니메이션 재생
	// TODO : 최적화 필요한지 체크
	if (GetWorld()->GetTimerManager().IsTimerActive(AttackResetTimer))
		GetWorld()->GetTimerManager().ClearTimer(AttackResetTimer);

	GetWorld()->GetTimerManager().SetTimer(
		AttackResetTimer,
		[this]() { this->AttackCount = 0; }, 
		ResetInterval, 
		false);

	// 애니메이션 재생
	++AttackCount;
	Player->AnimInst->PlayAttack(AttackCount);
}

void UPlayerAttack::ActivateHitCollider(bool bIsEnable)
{
	Player->HitCollider->SetCollisionEnabled(bIsEnable ? ECollisionEnabled::QueryAndPhysics: ECollisionEnabled::NoCollision);
}

void UPlayerAttack::OnActorOverlaped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if(OtherActor && OtherActor->IsA<ATDRPGEnemy>())
	{
		ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(OtherActor);
		int32 Damage = Player->DataComp->GetAttackPower();

		Enemy->TakeDamage(Damage);
	}
}
