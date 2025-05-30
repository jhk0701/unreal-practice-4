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
	TObjectPtr<class UCharacterData> dataComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerMove> moveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerAttack> attackComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerInteraction> interactComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<class UPlayerAnim> animInst;

	FOnInputBindDelegate OnInputBindDelegate;
	FOnUniqueInputDelegate OnAttackCalled;
	
	// 임시 히트박스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class USphereComponent> hitCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	TObjectPtr<class USphereComponent> interactCollider;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<class UTDRPGUWStatusBar> UIStatusBar;

public:
	ATDRPGPlayer();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Initialize();

	void InvokeAttackDelegate();
	inline const TObjectPtr<UCharacterData> GetData() const { return dataComp; }

	void TakeDamage(int32 Damage);
	void Die();

	bool GetMouseToWorld(FHitResult& OutResult);

};
