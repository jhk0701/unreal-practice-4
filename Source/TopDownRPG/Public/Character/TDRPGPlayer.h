#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDRPGPlayer.generated.h"

class UCharacterData;
class UPlayerMove;
class UPlayerAction;
class UPlayerInteraction;
class UCharacterAnimBase;
class UPlayerAnim;

class USpringArmComponent;
class UCameraComponent; 
class UInputComponent;
class USphereComponent;

class ATDRPGPlayerController;
class UEnhancedInputComponent;

DECLARE_MULTICAST_DELEGATE(FOnInitializeCompleted);
DECLARE_MULTICAST_DELEGATE(FOnInputInvoked);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInputBinded, UEnhancedInputComponent* , ATDRPGPlayerController* );

UCLASS()
class TOPDOWNRPG_API ATDRPGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	TObjectPtr<UCharacterData> DataComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	TObjectPtr<UPlayerMove> MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	TObjectPtr<UPlayerAction> ActionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	TObjectPtr<UPlayerInteraction> InteractComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPlayerAnim> AnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<USphereComponent> InteractCollider;

	FOnInitializeCompleted OnInitCompleted;

	FOnInputBinded OnInputBinded;
	FOnInputInvoked OnAttackInvoked;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> Camera;

public:
	ATDRPGPlayer();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	inline TObjectPtr<UCharacterData> GetData() const { return DataComp; }
	TObjectPtr<UCharacterAnimBase> GetAnim() const;

	void InvokeAttackDelegate();

	void TakeDamage(int32 Damage);
	void Die();

	bool GetMouseToWorld(FHitResult& OutResult);
	bool CheckPlayerIsDead() const;

private:
	void Initialize();
	void LoadConfig();
};
