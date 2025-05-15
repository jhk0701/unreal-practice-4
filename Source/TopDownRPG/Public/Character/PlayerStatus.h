// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerBaseComponent.h"
#include "Character/Status.h"
#include "PlayerStatus.generated.h"

UENUM(BlueprintType)
enum class EStatus : uint8
{
	Health UMETA(DisplayName = "HP"),
	Mana UMETA(DisplayName = "MP"),
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerStatus : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
public:
	UPlayerStatus();

	TMap<EStatus, TUniquePtr<Status>> Stat;

	void InitStatus(const TArray<EStatus>& StatusType, const TArray<uint32>& InitVal);
	
	// 공격력, 방어력 
	
};
