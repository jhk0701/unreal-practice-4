// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSkillListSlot.h"

#include "TDRPGEnum.h"
#include "Core/ResourceLoadManager.h"
#include "Data/SkillDataRow.h"
#include "Character/Skill/Skill.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWSkillListSlot::Bind(UDataModel* InModel)
{
	Super::Bind(InModel);
}


void UTDRPGUWSkillListSlot::Refresh()
{
	USkill* Skill = Cast<USkill>(Model);
	check(Skill);

	FSkillDataRow& Data = Skill->GetData();

	NameLabel->SetText(FText::FromName(Data.Name));

	FString InputType = FTDRPGEnum::EnumToString(Data.InputType);
	InputLabel->SetText(FText::FromString(FString::Printf(TEXT("[%s]"), *InputType)));

	// CostLabel->SetText
	FString CostStr = "";
	for(auto& Pair : Data.Requirement)
	{
		CostStr.Append(FTDRPGEnum::EnumToString(Pair.Key));
		CostStr.Append(FString::Printf(TEXT(" Cost %d"), Pair.Value));
	}

	CostLabel->SetText(FText::FromString(CostStr));
	CooldownLabel->SetText(FText::FromString(FString::Printf(TEXT("Cooldown %d sec"), Data.Cooldown)));

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
