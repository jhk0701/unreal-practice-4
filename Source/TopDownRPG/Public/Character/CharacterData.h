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

	// TODO : 버프 연산 : 합, 곱, 오버라이드
	// 오버라이드 시, 무조건 덮어쓰기
	// 한번에 여러가지 버프를 우선순위대로 연산해야함
	// 
	// 버프를 받으면 컨테이너에 저장
	// 컨테이너 구성에 OperType, Target, Value, ID
	// OperType 기준 오름차순 정렬
	// 정렬된대로 연산 진행


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
