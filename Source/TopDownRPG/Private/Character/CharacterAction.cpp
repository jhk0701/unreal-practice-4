// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAction.h"

#include "TDRPGConst.h"
#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"

#include "Character/Skill/Skill.h"


UCharacterAction::UCharacterAction()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAction::SetSkill(TArray<FString>& InSkillIDs)
{
	SkillMap.Empty();

	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();

	for (auto It = InSkillIDs.CreateConstIterator(); It; ++It)
	{
		USkill* Skill = NewObject<UActiveSkill>();
		Skill->Initialize(*It, GameData, GetOwner());

		SkillMap.Add(*It, Skill);

		if (It.GetIndex() == 0)
			DefaultAttack = Cast<UActiveSkill>(Skill);
	}
}