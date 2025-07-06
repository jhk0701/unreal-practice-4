// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"


class USkillConfig;
class UInputProcessor;
class UAnimMontage;

enum class ESkillDirection : uint8;
enum class EStatus : uint8;

struct FSkillDataRow;
struct FSkillInputContext;

DECLARE_MULTICAST_DELEGATE(FSkillEvent);

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API USkill : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<AActor> Owner;

	// 효과 객체
	UPROPERTY()
	TSoftObjectPtr<UParticleSystem> Effect;

	UPROPERTY()
	TSoftObjectPtr<UAnimMontage> Motion;

	int32 Range;
	int32 Size;
	ESkillDirection Direction;
	int32 MinDamage;
	int32 MaxDamage;
	TMap<EStatus, int32> Requirement;
	int32 Cooldown;

public:
	FSkillEvent OnSkillStarted;
	FSkillEvent OnSkillHitted;

	/// 스킬 객체 초기화
	virtual void Initialize(FSkillDataRow& InData, USkillConfig* InConfig, AActor* InOwner);

protected:
	/// 실질적인 스킬 호출 함수
	virtual void Activate(const FSkillInputContext& InContext);
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

	virtual void ShowEffect();
	virtual void InvokeSweep();
};


UCLASS()
class TOPDOWNRPG_API UPassiveSkill : public USkill
{
	GENERATED_BODY()

public:
	virtual void Activate(const FSkillInputContext& InContext) override;
};