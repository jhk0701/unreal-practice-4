// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWSkillSet.h"

#include "TDRPGEnum.h"
#include "UI/Element/TDRPGUWSkillSlotHolder.h"

#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>


void UTDRPGUWSkillSet::Bind(USkillSet* InSkillSet)
{
}

void UTDRPGUWSkillSet::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 슬롯 세팅
	if (SlotFactory)
	{
		uint8 Cnt = (uint8)ESkillInputKey::COUNT;

		for(uint8 i = 0; i < Cnt; ++i)
		{
			UTDRPGUWSkillSlot* Instance = CreateWidget<UTDRPGUWSkillSlot>(this, SlotFactory);
			
			UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(Container->AddChild(Instance));
			GridSlot->SetColumn(i % 4);
			GridSlot->SetRow(i / 4);

			ESkillInputKey Key =(ESkillInputKey)i;
			FText KeyText = FText::FromString(FTDRPGEnum::EnumToString(Key));
			Instance->SetKeyText(KeyText);
		}
	}
}