// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <Templates/UnrealTypeTraits.h>
#include "AssetLoadSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAssetLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	// template<typename T, typename TEnableIf<TIsDerivedFrom<T, UClass>::Value>::Type>
	template<class T>
	T* Load(const FString& Path);
};
