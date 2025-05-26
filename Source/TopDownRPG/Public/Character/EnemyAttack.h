// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAttack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UEnemyAttack : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Owner)
	TObjectPtr<class ATDRPGEnemy> enemy;

	// TODO : 공격 - 스킬들 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float curCooldown = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack|Setting")
	float attackCooldown = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack|Setting")
	float attackRange = 100.0f;

public:	
	UEnemyAttack();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack();
	inline bool IsAttacking() const { return bIsAttacking; }
	inline float GetAttackRange() const { return attackRange; }

	void ActivateHitCollider(bool bIsEnable);

	UFUNCTION()
	void OnActorOverlaped(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

};
