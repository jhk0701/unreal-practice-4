// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameDatabaseSystem.generated.h"

UENUM(BlueprintType)
enum class ETableType : uint8
{
	Character = 0,
	Leveling,

	COUNT
};

DECLARE_ENUM_TO_STRING(ETableType);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UGameDatabaseSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	TMap<ETableType, class UDataTable*> GameDatabase;
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void LoadGameDatas();
};
