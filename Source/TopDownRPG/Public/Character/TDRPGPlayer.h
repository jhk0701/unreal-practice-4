#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDRPGPlayer.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnUniqueInputDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInputBindDelegate, class UEnhancedInputComponent* , class ATDRPGPlayerController* );

UCLASS()
class TOPDOWNRPG_API ATDRPGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterStatus> statusComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr <class UCharacterAbility> abilityComp;

	// 임시 히트박스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class USphereComponent> hitCollider;

	FOnInputBindDelegate OnInputBindDelegate;
	FOnUniqueInputDelegate OnAttackCalled;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerMove> moveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerAttack> attackComp;

public:
	ATDRPGPlayer();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InvokeAttackDelegate();
	TObjectPtr<UCharacterStatus> GetStatus() { return statusComp; }

	void TakeDamage(int32 Damage);
	void Die();

	const FName GetTag() { return TEXT("Player"); }

};
