// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAction.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/EnemyAnim.h"

#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"

// Sets default values for this component's properties
UEnemyAction::UEnemyAction()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyAction::BeginPlay()
{
	Super::BeginPlay();

	bIsAttacking = false;
	CurCooldown = .0f;

	Enemy = Cast<ATDRPGEnemy>(GetOwner());

	Enemy->HitCollider->OnComponentBeginOverlap.AddDynamic(this, &UEnemyAction::OnActorOverlaped);
	ActivateHitCollider(false);
}

void UEnemyAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAttacking)
	{
		CurCooldown -= DeltaTime;
		
		if (CurCooldown <= .0f)
			bIsAttacking = false;
	}
}

void UEnemyAction::InvokeAttack()
{
	if (bIsAttacking)
		return;

	bIsAttacking = true;
	CurCooldown = AttackCooldown;

	PRINT_LOG(TEXT("Enemy Attack!"));
	Enemy->AnimInst->PlayAttack(0);
}

void UEnemyAction::InvokeSkill(int32 InIndex)
{
}


void UEnemyAction::ActivateHitCollider(bool bIsEnable)
{
	Enemy->HitCollider->SetCollisionEnabled(bIsEnable ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}

void UEnemyAction::OnActorOverlaped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if(OtherActor && OtherActor->IsA<ATDRPGPlayer>())
	{
		ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(OtherActor);
		int32 Damage = Enemy->DataComp->GetAttackPower();

		PRINT_LOG(TEXT("player take damage : %d"), Damage);

		Player->TakeDamage(Damage);
	}
}

