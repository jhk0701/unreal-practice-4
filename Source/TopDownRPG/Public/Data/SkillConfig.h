// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDRPGConst.h"
#include "SkillConfig.generated.h"

class ASkillEffectBase;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API USkillConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (AssetBundles = "SkillBundles"))
	TSoftObjectPtr<UAnimMontage> Motion;
	
	UPROPERTY(EditAnywhere, meta = (AssetBundles = "SkillBundles"))
	TSoftClassPtr<ASkillEffectBase> Effect;

	inline virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(FTDRPGConst::CONFIG_SKILL, GetFName());
	};
};
