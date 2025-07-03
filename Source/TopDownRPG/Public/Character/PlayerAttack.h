// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerInputComponent.h"
#include "PlayerAttack.generated.h"

class USkill;
class UActiveSkill;

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
	// 스킬 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Skill")
	TMap<FString, USkill*> SkillMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Skill")
	TObjectPtr<UActiveSkill> DefaultAttack;

public:
	UPlayerAttack();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;

	void Initialize(TArray<FString>& InSkillIDs);

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
