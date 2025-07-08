// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSkillSlot.h"

#include <Components/TextBlock.h>

void UTDRPGUWSkillSlot::SetKeyText(FText& InText)
{
	KeyLabel->SetText(InText);
}

void UTDRPGUWSkillSlot::Bind(UDataModel* InModel)
{
}

void UTDRPGUWSkillSlot::Unbind()
{
}

void UTDRPGUWSkillSlot::Refresh(UDataModel* InModel)
{
}
