// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterAction.h"
#include "EnemyAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UEnemyAction : public UCharacterAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Owner")
	TObjectPtr<class ATDRPGEnemy> Enemy;


	// TODO : 공격 - 스킬들 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float CurCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack|Setting")
	float AttackCooldown = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack|Setting")
	float AttackRange = 100.0f;

public:	
	UEnemyAction();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InvokeAttack() override;
	virtual void InvokeSkill(int32 InIndex) override;

	inline bool IsAttacking() const { return bIsAttacking; }
	inline const float GetAttackRange() { return AttackRange; }
};
