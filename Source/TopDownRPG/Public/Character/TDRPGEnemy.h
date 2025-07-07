#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDRPGEnemy.generated.h"

class ATDRPGPlayer;
class UCharacterData;
class UEnemyMove;
class UEnemyAction;

class UCharacterAnimBase;
class UEnemyAnim;

class UCapsuleComponent;
class UEnemyFSM;

UCLASS()
class TOPDOWNRPG_API ATDRPGEnemy : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	TObjectPtr<ATDRPGPlayer> Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<UCharacterData> DataComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<UEnemyMove> MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<UEnemyAction> ActionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<UEnemyAnim> AnimInst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<UCapsuleComponent> Collider;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine)
	TObjectPtr<UEnemyFSM> StateMachine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<USkeletalMeshComponent> SkinMesh;

public:
	ATDRPGEnemy();
	virtual void BeginPlay() override;

	inline TObjectPtr<UCharacterData> GetData() const { return DataComp; }
	TObjectPtr<UCharacterAnimBase> GetAnim() const;

	void TakeDamage(int32 Damage);
	void Die();

};
