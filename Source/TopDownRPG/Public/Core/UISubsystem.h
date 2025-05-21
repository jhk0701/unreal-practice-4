// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FString basePath = TEXT("/Game/4-UI/WBP_%s.WBP_%s_C");

	TMap<FName, class UTDRPGUserWidget*> uiMap;

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	template<typename T>
	T* CreateUI();
	template<typename T>
	T* GetUI();
};
