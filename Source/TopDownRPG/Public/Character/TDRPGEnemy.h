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
	TObjectPtr<class ATDRPGPlayer> target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterData> dataComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyMove> moveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyAttack> attackComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyAnim> animInst;

	// 임시 히트박스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class USphereComponent> hitCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCapsuleComponent> collider;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine)
	TObjectPtr<class UEnemyFSM> stateMachine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<USkeletalMeshComponent> skinMesh;

public:
	ATDRPGEnemy();
	virtual void BeginPlay() override;

	inline TObjectPtr<UCharacterData> GetData() const { return dataComp; }
	void TakeDamage(int32 Damage);
	void Die();

};
