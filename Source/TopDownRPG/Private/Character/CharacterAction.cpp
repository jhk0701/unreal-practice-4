// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAction.h"

#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/SkillDataRow.h"
#include "Character/Skill/Skill.h"


UCharacterAction::UCharacterAction()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAction::Initialize(TArray<FString>& InSkillIDs)
{
	SkillMap.Empty();

	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	for (FString& ID : InSkillIDs)
	{
		FSkillDataRow* SkillData = GameData->GetRow<FSkillDataRow>(ETableType::Skill, ID);
		check(SkillData);

		USkill* Skill;

		SkillData->Type == ESkillType::Active ?
			Skill = NewObject<UActiveSkill>() :
			Skill = NewObject<UPassiveSkill>();

		Skill->Initialize(*SkillData, GetOwner());

		SkillMap.Add(ID, Skill);

		if (SkillData->bIsDefaultAction)
			DefaultAttack = Cast<UActiveSkill>(Skill);
	}
}