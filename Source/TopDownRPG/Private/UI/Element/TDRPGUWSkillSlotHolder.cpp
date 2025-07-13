// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSkillSlotHolder.h"
#include "UI/DragDropWidget.h"

#include "Character/Skill/Skill.h"

#include "TopDownRPG/TopDownRPG.h"


bool UTDRPGUWSkillSlotHolder::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bIsDropped = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	if (USkill* Dropped = Cast<USkill>(InOperation->Payload))
	{
		OnSkillDropped.ExecuteIfBound(Dropped, Key);
	}

	return bIsDropped;
}
