#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inherit/Interactable.h"
#include "TDRPGPlayer.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnUniqueInputDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInputBindDelegate, class UEnhancedInputComponent* , class ATDRPGPlayerController* );

UCLASS()
class TOPDOWNRPG_API ATDRPGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterData> DataComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerMove> MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerAttack> AttackComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerInteraction> InteractComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<class UPlayerAnim> AnimInst;

	FOnInputBindDelegate OnInputBindDelegate;
	FOnUniqueInputDelegate OnAttackCalled;
	
	// 임시 히트박스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class USphereComponent> HitCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	TObjectPtr<class USphereComponent> InteractCollider;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> Camera;

	// TODO : UI 관리 분리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<class UTDRPGUWStatusBar> UIStatusBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<class UTDRPGUWQuickSlot> UIQuickSlot;

public:
	ATDRPGPlayer();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Initialize();

	void InvokeAttackDelegate();
	inline const TObjectPtr<UCharacterData> GetData() const { return DataComp; }

	void TakeDamage(int32 Damage);
	void Die();

	bool GetMouseToWorld(FHitResult& OutResult);
};
