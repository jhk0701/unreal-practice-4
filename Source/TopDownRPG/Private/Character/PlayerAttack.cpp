// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAttack.h"
#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterStatus.h"
#include "Character/CharacterAbility.h"
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

	player->hitCollider->OnComponentBeginOverlap.AddDynamic(this, &UPlayerAttack::OnActorOverlaped);
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
	if (player->animInst->IsAttackPlaying())
		return;

	player->InvokeAttackDelegate(); // 이동 기능은 꺼질 것
	
	// 커서 방향으로 바라보도록
	FHitResult hitResult;
	player->GetMouseToWorld(hitResult);

	FVector dir = hitResult.ImpactPoint - player->GetActorLocation();
	player->SetActorRotation(dir.ToOrientationQuat());

	// 애니메이션 재생
	// TODO : 최적화 필요한지 체크
	if (GetWorld()->GetTimerManager().IsTimerActive(attackResetTimer))
		GetWorld()->GetTimerManager().ClearTimer(attackResetTimer);

	GetWorld()->GetTimerManager().SetTimer(
		attackResetTimer, 
		[this]() {this->attackCount = 0; }, 
		resetInterval, 
		false);

	// 애니메이션 재생
	++attackCount;
	player->animInst->PlayAttack(attackCount);
}

void UPlayerAttack::ActivateHitCollider(bool bIsEnable)
{
	player->hitCollider->SetCollisionEnabled(bIsEnable ? ECollisionEnabled::QueryAndPhysics: ECollisionEnabled::NoCollision);
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
		ATDRPGEnemy* enemy = Cast<ATDRPGEnemy>(OtherActor);
		int32 damage = player->abilityComp->GetAttackPower();

		enemy->TakeDamage(damage);
	}
}
