// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Status.h"
#include "CharacterStatus.generated.h"

UENUM(BlueprintType)
enum class EStatus : uint8
{
	Hp UMETA(DisplayName = "Health Point"),
	Mp UMETA(DisplayName = "Mana Point"),
};

/**
 * 플레이어 스테이터스 컴포넌트
 */
UCLASS()
class TOPDOWNRPG_API UCharacterStatus : public UActorComponent
{
	GENERATED_BODY()

public:
	// 레벨
	int32 Lv;

	// 경험치
	TUniquePtr<Status> Exp;
	
	// 체력, 마나
	TMap<EStatus, TUniquePtr<Status>> Stat;

	bool bIsDead = false;
	
public:
	UCharacterStatus();

	void InitLvAndExp(uint32 InitLv, uint32 InitExp);
	void AddExp(uint32 Value) { Exp->Add(Value); }
	void CheckExp(uint32 Max, uint32 Current);
	void LevelUp();

	void InitStatus(const TArray<EStatus>& StatusType, const TArray<uint32>& InitVal);
	bool SubtractStat(EStatus Type, uint32 Value) { return Stat[Type]->TrySubtract(Value); }

	void CheckPlayerIsDead(uint32 Max, uint32 Current);
	void OnPlayerDead();
};
