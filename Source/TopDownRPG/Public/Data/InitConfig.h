// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CommonConst.h"
#include "InitConfig.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UInitConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FString> ConfigsToInit;
	
	FPrimaryAssetId GetPrimaryAssetId() const override 
	{
		return FPrimaryAssetId(CommonConst::AssetType_InitConfig, CommonConst::AssetType_InitConfig);
	};

};
