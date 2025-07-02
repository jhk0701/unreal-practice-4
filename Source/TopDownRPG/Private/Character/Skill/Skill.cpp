// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Skill.h"
#include "Character/Skill/SkillEffectBase.h"

#include "Data/SkillDataRow.h"

#include "TopDownRPG/TopDownRPG.h"

void USkill::Initialize(const FSkillDataRow& InData, const AActor& InOwner)
{
	PRINT_LOG(TEXT("SkillBase Init : %s"), *InData.Name.ToString());

	// 스킬 구성
	
	// 태그 설정
	// Effect->Tags.Add(InOwner.Tags[0]);
}

void UActiveSkill::Activate()
{
}

void UPassiveSkill::Activate()
{
}
