// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

struct FSkillDataRow;
class USkillConfig;
class ASkillEffectBase;

class UInputProcessor;
struct FSkillInputContext;

class UAnimMontage;

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API USkill : public UObject
{
	GENERATED_BODY()

protected:
	// 효과 객체
	UPROPERTY()
	TSoftClassPtr<ASkillEffectBase> Effect;

	// 오브젝트 풀링으로 관리
	TQueue<ASkillEffectBase*> EffectPool;

	UPROPERTY()
	TSoftObjectPtr<UAnimMontage> Motion;

	UPROPERTY()
	TObjectPtr<AActor> Owner;

public:
	/// 스킬 객체 초기화
	virtual void Initialize(FSkillDataRow& InData, USkillConfig* InConfig, AActor* InOwner);

protected:
	/// 실질적인 스킬 호출 함수
	virtual void Activate(const FSkillInputContext& InContext) {};

	ASkillEffectBase* GetEffect();
	ASkillEffectBase* CreateEffect();
	void ReleaseEffect(AActor* InInstance);
};

UCLASS()
class TOPDOWNRPG_API UActiveSkill : public USkill
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UInputProcessor> Input;		// 입력 처리 객체

	float Cooldown;
	FTimerHandle CooldownTimer;

public:
	/// 스킬 객체 초기화
	virtual void Initialize(FSkillDataRow& InData, USkillConfig* InConfig, AActor* InOwner) override;
	
	/// 키 입력 시, 스킬 실행 함수
	virtual void InvokeSkill();

protected:
	virtual void Activate(const FSkillInputContext& InContext) override;

	/// 키 입력에 처리 시 호출 콜백
	virtual void OnInputProcessed(const FSkillInputContext& InContext);
};


UCLASS()
class TOPDOWNRPG_API UPassiveSkill : public USkill
{
	GENERATED_BODY()

public:
	virtual void Activate(const FSkillInputContext& InContext) override;
};