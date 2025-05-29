// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CommonConst.h"
#include "CharacterConfig.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UCharacterConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName CharName;

	UPROPERTY(EditAnywhere, meta = (AssetBundles = "CharacterBundles"))
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (AssetBundles = "CharacterBundles"))
	TSoftClassPtr<UAnimInstance> Animation;

	inline virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(CommonConst::AssetType_CharacterConfig, GetFName());
	};
};
