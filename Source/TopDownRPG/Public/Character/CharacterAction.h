// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAction.generated.h"

class USkill;
class UActiveSkill;

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UCharacterAction : public UActorComponent
{
	GENERATED_BODY()

protected:
	// 스킬 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Skill")
	TMap<FString, USkill*> SkillMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack|Skill")
	TObjectPtr<UActiveSkill> DefaultAttack;

public:	
	UCharacterAction();
	virtual void SetSkill(TArray<FString>& InSkillIDs);

	virtual void InvokeAttack() {};
	virtual void InvokeSkill(int32 InIndex) {};

};
