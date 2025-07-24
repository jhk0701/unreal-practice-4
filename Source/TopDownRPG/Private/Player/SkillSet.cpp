// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkillSet.h"

#include "TDRPGConst.h"
#include "TDRPGEnum.h"
#include "Character/Skill/Skill.h"

USkillSet::USkillSet()
{
	uint8 Cnt = (uint8)ESkillInputKey::COUNT;

	for(uint8 i = 0; i < Cnt; ++i)
		Map.Add((ESkillInputKey)i, FTDRPGConst::EMPTY_ID);
}

void USkillSet::InitSet(ESkillInputKey InKey, FString& InID)
{
	Map[InKey] = InID;
	OnSlotUpdated.Broadcast(InKey);
}

void USkillSet::Register(ESkillInputKey InKey, UActiveSkill* InSkill)
{
	Map[InKey] = InSkill->GetID();
	OnSlotUpdated.Broadcast(InKey);
}

void USkillSet::Unregister(ESkillInputKey InKey)
{
	Map[InKey] = FTDRPGConst::EMPTY_ID;
	OnSlotUpdated.Broadcast(InKey);
}
