// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

class ASkillEffectBase;
struct FSkillDataRow;

class UInputProcessor;

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
	virtual void Initialize(const FSkillDataRow& InData, const AActor& InOwner);
	virtual void Activate() {};
};

UCLASS()
class TOPDOWNRPG_API UActiveSkill : public USkill
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
};

UCLASS()
class TOPDOWNRPG_API UPassiveSkill : public USkill
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
};