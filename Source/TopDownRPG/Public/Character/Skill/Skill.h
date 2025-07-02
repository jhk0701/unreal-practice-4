// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

class ASkillEffectBase;
struct FSkillDataRow;

class UInputProcessor;
struct FSkillInputContext;

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API USkill : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<ASkillEffectBase> Effect;	// 효과 객체

	UPROPERTY()
	TObjectPtr<UInputProcessor> Input;		// 입력 처리 객체

public:
	/// <summary>
	/// 스킬 객체 초기화
	/// </summary>
	/// <param name="InData"></param>
	/// <param name="InOwner"></param>
	virtual void Initialize(const FSkillDataRow& InData, const AActor& InOwner);
	
	/// <summary>
	/// 키 입력 시, 스킬 실행 함수
	/// </summary>
	virtual void InvokeSkill();

protected:
	/// <summary>
	/// 키 입력에 처리 시 호출 콜백
	/// </summary>
	/// <param name="InContext"></param>
	virtual void OnInputProcessed(const FSkillInputContext& InContext);

	/// <summary>
	/// 실질적인 스킬 호출 함수
	/// </summary>
	virtual void Activate();
};

UCLASS()
class TOPDOWNRPG_API UActiveSkill : public USkill
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
};

UCLASS()
class TOPDOWNRPG_API UPassiveSkill : public USkill
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
};