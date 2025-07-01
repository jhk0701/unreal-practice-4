// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

class ASkillEffectBase;

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API USkillBase : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<ASkillEffectBase> Effect; // 효과 객체

public:
	virtual void Initialize(const FString& InSkillID);
	virtual void Activate() {};
};
