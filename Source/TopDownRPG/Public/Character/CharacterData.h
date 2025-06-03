// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Status.h"
#include "TDRPGEnum.h"
#include "CharacterData.generated.h"

struct FCharacterDataRow;

DECLARE_MULTICAST_DELEGATE(FOnStatusEmpty);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UCharacterData : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, Category = "ID")
	FString CharID;

	TMap<EStatus, TUniquePtr<Status>> Stat;	// 체력, 마나
	TMap<EAbility, uint32> Ability;	// 힘, 민첩, 지능

	// 버프 연산 : 합, 곱, 덮어쓰기

	UPROPERTY()
	bool bIsDead = false;
	
	FOnStatusEmpty OnCharacterDead;

public:	
	UCharacterData();

	void Initialize(uint32 InLv, FCharacterDataRow* InData);

	inline bool TrySubtractStat(EStatus Type, uint32 Value) const { return Stat[Type]->TrySubtract(Value); }
	inline void SubtractStat(EStatus Type, uint32 Value) { Stat[Type]->Subtract(Value); }
	void CheckIsDead(uint32 Max, uint32 Current);

	uint32 GetAttackPower();
	uint32 GetDefensePower();

	void Debugging();
};
