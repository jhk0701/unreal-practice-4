// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterConfig.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UCharacterConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> SkinnedMesh;	// 메쉬
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UCharacterAnimBase> AnimBlueprint; // 애니메이션 블루프린트
	
	// /Script/TopDownRPG.CharacterConfig'/Game/6-DataAsset/Test.Test'
};
