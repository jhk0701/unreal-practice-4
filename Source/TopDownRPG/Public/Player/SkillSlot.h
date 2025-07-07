// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillSlot.generated.h"

class UActiveSkill;
enum class ESkillInputKey :uint8;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSkillSlotUpdated, ESkillInputKey);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API USkillSlot : public UObject
{
	GENERATED_BODY()

public:
	FOnSkillSlotUpdated OnSlotUpdated;
	
private:
	UPROPERTY()
	TMap<ESkillInputKey, UActiveSkill*> SkillSlot;

public:
	USkillSlot();
	inline UActiveSkill* GetSlot(ESkillInputKey InKey) const { return SkillSlot[InKey]; };
	void Register(ESkillInputKey InKey, UActiveSkill* InSkill);
	void Unregister(ESkillInputKey InKey);

};
