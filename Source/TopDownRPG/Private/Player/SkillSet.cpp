// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkillSet.h"

#include "TDRPGEnum.h"
#include "Character/Skill/Skill.h"


USkillSet::USkillSet()
{
	uint8 Cnt = (uint8)ESkillInputKey::COUNT;

	for(uint8 i = 0; i < Cnt; ++i)
		Map.Add((ESkillInputKey)i, nullptr);
}

void USkillSet::Register(ESkillInputKey InKey, UActiveSkill* InSkill)
{
	Map[InKey] = InSkill;

	OnSlotUpdated.Broadcast(InKey);
}

void USkillSet::Unregister(ESkillInputKey InKey)
{
	Map[InKey] = nullptr;

	OnSlotUpdated.Broadcast(InKey);
}
