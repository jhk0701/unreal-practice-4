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

	// 정리 절차
	if (Model && Model->IsA<UActiveSkill>())
	{
		UActiveSkill* ActiveSkill = Cast<UActiveSkill>(Model);
		ActiveSkill->OnCooldownStarted.RemoveAll(this);
		ActiveSkill->OnCooldownEnded.RemoveAll(this);
	}

	Model = InModel;
	Refresh();

	// 구독 추가
	if (Model && Model->IsA<UActiveSkill>())
	{
		UActiveSkill* ActiveSkill = Cast<UActiveSkill>(Model);
		ActiveSkill->OnCooldownStarted.AddUObject(this, &UTDRPGUWSkillSlot::OnCooldownStart);
		ActiveSkill->OnCooldownEnded.AddUObject(this, &UTDRPGUWSkillSlot::OnCooldownEnd);
	}
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

void UTDRPGUWSkillSlot::OnCooldownStart()
{
	IconImage->SetOpacity(0.2f);
}

void UTDRPGUWSkillSlot::OnCooldownEnd()
{
	IconImage->SetOpacity(1.0f);
}
