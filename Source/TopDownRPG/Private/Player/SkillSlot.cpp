// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkillSlot.h"

#include "TDRPGEnum.h"
#include "Character/Skill/Skill.h"

USkillSlot::USkillSlot()
{
	uint8 Cnt = (uint8)ESkillInputKey::COUNT;

	for(uint8 i = 0; i < Cnt; ++i)
		SkillSlot.Add((ESkillInputKey)i, nullptr);
}

void USkillSlot::Register(ESkillInputKey InKey, UActiveSkill* InSkill)
{
	SkillSlot[InKey] = InSkill;

	OnSlotUpdated.Broadcast(InKey);
}

void USkillSlot::Unregister(ESkillInputKey InKey)
{
	SkillSlot[InKey] = nullptr;

	OnSlotUpdated.Broadcast(InKey);
}
