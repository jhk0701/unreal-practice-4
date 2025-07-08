// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataModel.generated.h"

class UGameDataManager;

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API UDataModel : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FString ID;

	UPROPERTY()
	TObjectPtr<UGameDataManager> DB;

public:
	virtual void Initialize(const FString& InID, UGameDataManager* InDB);
	inline const FString& GetID() const { return ID; }
};