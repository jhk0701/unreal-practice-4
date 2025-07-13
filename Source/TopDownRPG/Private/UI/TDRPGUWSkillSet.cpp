// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWSkillSet.h"
#include "UI/Element/TDRPGUWSkillSlotHolder.h"

#include "TDRPGEnum.h"
#include "TDRPGConst.h"

#include "Player/SkillSet.h"
#include "Character/Skill/Skill.h"
#include "Character/CharacterAction.h"

#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>


void UTDRPGUWSkillSet::Bind(USkillSet* InSkillSet, UCharacterAction* InAction)
{
	BindedSkillSet = InSkillSet;
	BindedSkillSet->OnSlotUpdated.AddUObject(this, &UTDRPGUWSkillSet::OnSlotUpdated);

	BindedAction = InAction;
}

void UTDRPGUWSkillSet::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 슬롯 세팅
	if (SlotFactory)
	{
		SlotInst.Empty();
		uint8 Cnt = (uint8)ESkillInputKey::COUNT;

		for(uint8 i = 0; i < Cnt; ++i)
		{
			UTDRPGUWSkillSlotHolder* Inst = CreateWidget<UTDRPGUWSkillSlotHolder>(this, SlotFactory);
			
			UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(Container->AddChild(Inst));
			GridSlot->SetColumn(i % 4);
			GridSlot->SetRow(i / 4);

			ESkillInputKey Key =(ESkillInputKey)i;
			Inst->SetKey(Key);
			Inst->OnSkillDropped.BindUObject(this, &UTDRPGUWSkillSet::OnSkillDropped);

			SlotInst.Add(Key, Inst);
		}
	}
}

void UTDRPGUWSkillSet::OnSlotUpdated(ESkillInputKey& InKey)
{
	// 슬롯 업데이트 이어서하기
	FString& SkillID = BindedSkillSet->GetSkill(InKey);

	if (SkillID == FTDRPGConst::EMPTY_ID)
		return;

	SlotInst[InKey]->Bind(BindedAction->GetSkill(SkillID));
}

void UTDRPGUWSkillSet::OnSkillDropped(USkill* InSkill, ESkillInputKey& InKey)
{
	if (!InSkill)
		return;

	if (UActiveSkill* ActiveSkill = Cast<UActiveSkill>(InSkill))
		BindedSkillSet->Register(InKey, ActiveSkill);
}
