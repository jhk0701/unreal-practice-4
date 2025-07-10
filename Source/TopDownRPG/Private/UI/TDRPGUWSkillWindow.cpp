// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWSkillWindow.h"

#include "Character/PlayerAction.h"
#include "Character/Skill/Skill.h"

#include "UI/Element/TDRPGUWSkillListSlot.h"

#include <Components/ScrollBox.h>
#include <Components/Button.h>


void UTDRPGUWSkillWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);
}

void UTDRPGUWSkillWindow::Bind(UPlayerAction* InPlayerAction)
{
	BindedAction = InPlayerAction;
	Refresh();
}

void UTDRPGUWSkillWindow::Refresh()
{
	if (!SlotFactory)
		return;

	TArray<FString> IDs;
	BindedAction->GetSkillIDs(IDs);

	// 슬롯 동적 생성
	int32 Size = IDs.Num();
	ListSlots.Init(nullptr, Size);

	for (int32 i = 0; i < Size; ++i)
	{
		UTDRPGUWSkillListSlot* Instance = CreateWidget<UTDRPGUWSkillListSlot>(this, SlotFactory);
		
		Container->AddChild(Instance);
		ListSlots.Add(Instance);

		Instance->Bind(BindedAction->GetSkill(IDs[i]));
	}
}


