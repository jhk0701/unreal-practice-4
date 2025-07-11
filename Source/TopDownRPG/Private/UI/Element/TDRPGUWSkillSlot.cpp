// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSkillSlot.h"

#include "TDRPGEnum.h"
#include "Core/ResourceLoadManager.h"

#include "Data/SkillDataRow.h"
#include "Character/Skill/Skill.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWSkillSlot::SetKey(ESkillInputKey& InKey)
{
	Key = InKey;
	KeyLabel->SetText(FText::FromString(FTDRPGEnum::EnumToString(Key)));
}

void UTDRPGUWSkillSlot::Bind(UDataModel* InModel)
{
	if (!InModel)
		return;

	Model = InModel;
	Refresh();
}

void UTDRPGUWSkillSlot::Unbind()
{
	Model = nullptr;
	Clear();
}

void UTDRPGUWSkillSlot::Refresh()
{
	USkill* Skill = Cast<USkill>(Model);
	check(Skill);

	FSkillDataRow& Data = Skill->GetData();
	UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	Resource->Load(Data.Thumbnail, FOnResourceLoaded::CreateLambda(
		[this](UObject* Loaded) 
		{
			if (UTexture2D* LoadedTex = Cast<UTexture2D>(Loaded))
			{
				IconImage->SetBrushFromTexture(LoadedTex, true);
				IconImage->SetOpacity(1.0f);
				IconImage->SetVisibility(ESlateVisibility::Visible);
			}
		}
	));
}
