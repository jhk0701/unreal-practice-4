// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerInputComponent.h"
#include "PlayerAttack.generated.h"


// TODO : EnemyAttack과 리팩토링할것
// 방향 : PlayerInputConponent 기능을 인터페이스화
// EnemyAttack과 일치하는 부분은 CharacterAttack 으로 리팩토링해서 파생형을 사용
// PlayerAttack은 IInputHandler 상속해서 사용하도록 구현
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerAttack : public UPlayerInputComponent
{
	GENERATED_BODY()

protected:
	FTimerHandle AttackResetTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float ResetInterval = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Combo")
	int32 AttackCount = 0;

	// 스킬 데이터
	

public:
	UPlayerAttack();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;

	void InputAttack(const FInputActionValue& InputValue);
	void InvokeAttack();
	void ActivateHitCollider(bool bIsEnable);

	UFUNCTION()
	void OnActorOverlaped(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
};
