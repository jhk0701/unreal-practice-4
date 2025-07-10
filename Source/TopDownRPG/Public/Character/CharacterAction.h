// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAction.generated.h"

class USkill;
class UActiveSkill;

enum class EStatus: uint8;

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UCharacterAction : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Skill")
	TObjectPtr<UActiveSkill> DefaultAttack;

	// 스킬 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Skill")
	TMap<FString, USkill*> SkillMap;


public:	
	UCharacterAction();
	virtual void SetSkill(TArray<FString>& InSkillIDs);
	inline void GetSkillIDs(TArray<FString>& Output) { SkillMap.GetKeys(Output); };
	inline USkill* GetSkill(const FString& InKey) { return SkillMap[InKey]; };

	virtual void InvokeAttack() {};
	virtual void InvokeSkill(uint32 InIndex) {};
	virtual bool TryUseResource(const TMap<EStatus, int32>& InRequirement) { return true; };

};
