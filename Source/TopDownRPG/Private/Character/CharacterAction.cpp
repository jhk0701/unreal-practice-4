// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAction.h"

#include "TDRPGConst.h"
#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/SkillDataRow.h"
#include "Data/SkillConfig.h"

#include "Character/Skill/Skill.h"


UCharacterAction::UCharacterAction()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAction::SetSkill(TArray<FString>& InSkillIDs)
{
	SkillMap.Empty();

	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	for (FString& ID : InSkillIDs)
	{
		// Skill 데이터 호출
		FSkillDataRow* SkillData = GameData->GetRow<FSkillDataRow>(ETableType::Skill, ID);
		check(SkillData);

		USkill* Skill;

		SkillData->Type == ESkillType::Active ?
			Skill = NewObject<UActiveSkill>() :
			Skill = NewObject<UPassiveSkill>();

		// Skill Config 로드
		FPrimaryAssetId ConfigID(FTDRPGConst::CONFIG_SKILL, *ID);
		UPrimaryDataAsset* DataAsset = GameData->LoadPrimaryAssetData(ConfigID);
		check(DataAsset);

		USkillConfig* Config = Cast<USkillConfig>(DataAsset);

		Skill->Initialize(*SkillData, Config, GetOwner());

		SkillMap.Add(ID, Skill);

		if (SkillData->bIsDefaultAction)
			DefaultAttack = Cast<UActiveSkill>(Skill);
	}
}