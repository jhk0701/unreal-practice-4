// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ResourceLoadManager.generated.h"

DECLARE_DELEGATE_OneParam(FOnResourceLoaded, UObject*);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UResourceLoadManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void Load(FSoftObjectPath& InPath, FOnResourceLoaded& OnCompleteDelegate);
};
