// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillSet.generated.h"

class UActiveSkill;
enum class ESkillInputKey :uint8;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSkillSlotUpdated, ESkillInputKey);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API USkillSet : public UObject
{
	GENERATED_BODY()

public:
	FOnSkillSlotUpdated OnSlotUpdated;
	
private:
	UPROPERTY()
	TMap<ESkillInputKey, UActiveSkill*> Map;

public:
	USkillSet();
	inline UActiveSkill* GetSkill(ESkillInputKey InKey) const { return Map[InKey]; };
	void Register(ESkillInputKey InKey, UActiveSkill* InSkill);
	void Unregister(ESkillInputKey InKey);

};
