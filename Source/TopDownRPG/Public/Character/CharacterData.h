// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Status.h"
#include "CharacterData.generated.h"

struct FCharacterDataRow;

UENUM(BlueprintType)
enum class EStatus : uint8
{
	Hp UMETA(DisplayName = "Health Point"),
	Mp UMETA(DisplayName = "Mana Point"),

	COUNT
};

UENUM(BlueprintType)
enum class EAbility : uint8
{
	Str UMETA(DisplayName = "Strength"),
	Dex UMETA(DisplayName = "Dexterity"),
	Int UMETA(DisplayName = "Intelligence"),

	COUNT
};

DECLARE_MULTICAST_DELEGATE(FOnStatusEmpty);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UCharacterData : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, Category = "ID")
	FString CharID;

	// 레벨
	UPROPERTY()
	uint32 Lv;

	// 경험치
	TUniquePtr<Status> Exp;
	// 체력, 마나
	TMap<EStatus, TUniquePtr<Status>> Stat;

	// 힘, 민첩, 지능
	UPROPERTY()
	TMap<EAbility, uint32> Ability;

	UPROPERTY()
	bool bIsDead = false;
	
	FOnStatusEmpty OnCharacterDead;

public:	
	UCharacterData();

	void Initialize(uint32 InLv, uint32 InExp, FCharacterDataRow* InData);

	inline void AddExp(uint32 Value) { Exp->Add(Value); }
	void CheckExp(uint32 Max, uint32 Current);
	void LevelUp();

	inline bool TrySubtractStat(EStatus Type, uint32 Value) const { return Stat[Type]->TrySubtract(Value); }
	inline void SubtractStat(EStatus Type, uint32 Value) { Stat[Type]->Subtract(Value); }
	void CheckIsDead(uint32 Max, uint32 Current);

	uint32 GetAttackPower();
	uint32 GetDefensePower();

	void Debugging();
};
