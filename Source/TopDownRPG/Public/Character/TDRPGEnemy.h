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
	TObjectPtr<class UCapsuleComponent> collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterStatus> statusComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterAbility> abilityComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyMove> moveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyAttack> attackComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyAnim> animInst;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine)
	TObjectPtr<class UEnemyFSM> stateMachine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<USkeletalMeshComponent> skinMesh;

public:
	ATDRPGEnemy();
	virtual void BeginPlay() override;

	TObjectPtr<UCharacterStatus> GetStatus() const { return statusComp; }
	void TakeDamage(int32 Damage);
	void Die();

	const FName GetTag() { return TEXT("Enemy"); }
};
