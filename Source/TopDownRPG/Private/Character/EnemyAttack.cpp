// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAttack.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/EnemyAnim.h"
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"

// Sets default values for this component's properties
UEnemyAttack::UEnemyAttack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyAttack::BeginPlay()
{
	Super::BeginPlay();

	bIsAttacking = false;
	curCooldown = .0f;

	enemy = Cast<ATDRPGEnemy>(GetOwner());
	enemy->hitCollider->OnComponentBeginOverlap.AddDynamic(this, &UEnemyAttack::OnActorOverlaped);
	ActivateHitCollider(false);
}

void UEnemyAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAttacking)
	{
		curCooldown -= DeltaTime;
		
		if (curCooldown <= .0f)
			bIsAttacking = false;
	}
}

void UEnemyAttack::Attack()
{
	if (bIsAttacking)
		return;

	bIsAttacking = true;
	curCooldown = attackCooldown;

	PRINT_LOG(TEXT("Enemy Attack!"));
	enemy->animInst->PlayAttack(0);
}

void UEnemyAttack::ActivateHitCollider(bool bIsEnable)
{
	enemy->hitCollider->SetCollisionEnabled(bIsEnable ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}

void UEnemyAttack::OnActorOverlaped(
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
		ATDRPGPlayer* player = Cast<ATDRPGPlayer>(OtherActor);
		int32 damage = enemy->dataComp->GetAttackPower();

		PRINT_LOG(TEXT("player take damage : %d"), damage);

		player->TakeDamage(damage);
	}
}

