#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDRPGEnemy.generated.h"

UCLASS()
class TOPDOWNRPG_API ATDRPGEnemy : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	TObjectPtr<class ATDRPGPlayer> Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterData> DataComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyMove> MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyAttack> AttackComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyAnim> AnimInst;

	// 임시 히트박스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class USphereComponent> HitCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCapsuleComponent> Collider;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine)
	TObjectPtr<class UEnemyFSM> StateMachine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<USkeletalMeshComponent> SkinMesh;

public:
	ATDRPGEnemy();
	virtual void BeginPlay() override;

	inline TObjectPtr<UCharacterData> GetData() const { return DataComp; }
	void TakeDamage(int32 Damage);
	void Die();

};
