// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillSet.generated.h"

class USkill;
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
	// 여기서는 스킬 객체가 아니라 접근할 수 있는 key를 바인딩하는 용도로 하는 것이 적당할 듯
	UPROPERTY()
	TMap<ESkillInputKey, FString> Map;

public:
	USkillSet();

	inline FString& GetSkill(ESkillInputKey InKey) { return Map[InKey]; };
	void Register(ESkillInputKey InKey, UActiveSkill* InSkill);
	void Unregister(ESkillInputKey InKey);

};
