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
	TObjectPtr<class UCharacterStatus> statusComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr <class UCharacterAbility> abilityComp;

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

	// 임시 UI 테스트용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UITemp")
	TSubclassOf<class UTDRPGUWStatusBar> StatusBarFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UITemp")
	TObjectPtr<UTDRPGUWStatusBar> StatusBarInst;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	TObjectPtr<USphereComponent> interactionCollider;

public:
	ATDRPGPlayer();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InvokeAttackDelegate();
	inline TObjectPtr<UCharacterStatus> GetStatus() const { return statusComp; }

	void TakeDamage(int32 Damage);
	void Die();

	bool GetMouseToWorld(FHitResult& OutResult);

};
