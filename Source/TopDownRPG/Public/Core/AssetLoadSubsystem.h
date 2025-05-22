// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <Templates/EnableIf.h>
#include "AssetLoadSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAssetLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	template<class T>
	inline typename TEnableIf<TIsDerivedFrom<T, UObject>::Value, T*>::type
	Load(const FString& Path) 
	{
		return LoadObject<T>(nullptr, *Path);
	}
};
