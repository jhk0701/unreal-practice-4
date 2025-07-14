// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataModel.h"
#include "Data/SkillDataRow.h"
#include "Skill.generated.h"

enum class EStatus : uint8;
enum class ESkillDirection : uint8;
class USkillConfig;
class UInputProcessor;
class UAnimMontage;
struct FSkillInputContext;

DECLARE_MULTICAST_DELEGATE(FSkillEvent);

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API USkill : public UDataModel
{
	GENERATED_BODY()

public:
	FSkillEvent OnSkillStarted;
	FSkillEvent OnSkillHitted;

	/// 스킬 객체 초기화
	virtual void Initialize(const FString& InID, UGameDataManager* InDB, AActor* InOwner);
	inline FSkillDataRow& GetData() { return Data; }

protected:
	FSkillDataRow Data;

	UPROPERTY()
	TObjectPtr<AActor> Owner;

	// 효과 객체
	UPROPERTY()
	TSoftObjectPtr<UParticleSystem> Effect;

	UPROPERTY()
	TSoftObjectPtr<UAnimMontage> Motion;

	/// 실질적인 스킬 호출 함수
	virtual void Activate(const FSkillInputContext& InContext);
};

UCLASS()
class TOPDOWNRPG_API UActiveSkill : public USkill
{
	GENERATED_BODY()

public:
	/// 스킬 객체 초기화
	virtual void Initialize(const FString& InID, UGameDataManager* InDB, AActor* InOwner) override;
	
	/// 키 입력 시, 스킬 실행 함수
	virtual void InvokeSkill();
	
	inline bool IsInCooldown() { return Cooldown > 0.0f; }

	FSkillEvent OnCooldownStarted;
	FSkillEvent OnCooldownEnded;

protected:
	UPROPERTY()
	TObjectPtr<UInputProcessor> Input;		// 입력 처리 객체

	// 쿨타임
	float Cooldown = 0.0f;
	FTimerHandle CooldownTimer;

	virtual void Activate(const FSkillInputContext& InContext) override;

	/// 키 입력에 처리 시 호출 콜백
	virtual void OnInputProcessed(const FSkillInputContext& InContext);

	virtual void ShowEffect();
	virtual void InvokeSweep();
	virtual void AdjustDamage(const TArray<FHitResult>& InHits);
};

UCLASS()
class TOPDOWNRPG_API UPassiveSkill : public USkill
{
	GENERATED_BODY()

public:
	virtual void Activate(const FSkillInputContext& InContext) override;
};