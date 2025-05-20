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
	player->InvokeAttackDelegate(); // 이동 기능은 꺼질 것
	ActivateHitCollider(true);

	// 애니메이션 재생
	player->animInst->PlayAttack(0);
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
	PRINT_LOG(TEXT("Actor overlaped"));
		
	if(OtherActor && OtherActor->IsA<ATDRPGEnemy>())
	{
		PRINT_LOG(TEXT("Actor is enemy"));
		ATDRPGEnemy* enemy = Cast<ATDRPGEnemy>(OtherActor);
		int32 damage = player->abilityComp->GetAttackPower();

		enemy->TakeDamage(damage);
	}
}
