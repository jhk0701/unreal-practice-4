// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Skill.h"
#include "Character/Skill/SkillEffectBase.h"

#include "TDRPGEnum.h"
#include "Data/SkillDataRow.h"
#include "Character/Input/InputProcessor.h"

#include "TopDownRPG/TopDownRPG.h"

void USkill::Initialize(const FSkillDataRow& InData, const AActor& InOwner)
{
	PRINT_LOG(TEXT("SkillBase Init : %s"), *InData.Name.ToString());

	// 입력 처리 설정
	Input = FInputProcessorFactory::GetInstance(InData.InputType, InOwner.GetWorld());
	Input->OnInputProcessed.BindUObject(this, &USkill::OnInputProcessed);

	// 스킬 구성
	// TODO : 효과 구성
}

void USkill::InvokeSkill()
{
	Input->Process();
}

void USkill::OnInputProcessed(const FSkillInputContext& InContext)
{
	Activate();
}

void USkill::Activate()
{
	PRINT_LOG(TEXT("Skill Activate"));
}

/// <summary>
/// 액티브 스킬 발동
/// </summary>
void UActiveSkill::Activate()
{
	Super::Activate();
}

/// <summary>
/// 패시브 발동
/// </summary>
void UPassiveSkill::Activate()
{
}
