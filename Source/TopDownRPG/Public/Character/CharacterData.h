// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Status.h"
#include "Item/Function/FunctionContext.h"
#include "CharacterData.generated.h"

enum class EStatus : uint8;
enum class EAbility : uint8;
enum class EEquipType : uint8;
class UEquipment;
class UItemFuncBase;
struct FCharacterDataRow;

DECLARE_MULTICAST_DELEGATE(FOnStatusEmpty);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UCharacterData : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "ID")
	FString ClassID;

	TMap<EStatus, TUniquePtr<FStatus>> Stat;	// 체력, 마나
	TUniquePtr<FStatus> Shield; // 캐릭터 쉴드

	TMap<EStatus, uint32> BaseStatus;
	TMap<EAbility, uint32> BaseAbility;

	TMap<EStatus, uint32> EquipmentStatus;
	TMap<EAbility, uint32> EquipmentAbility;

	// TODO: 버프 연산 
	// 한번에 여러가지 버프를 우선순위대로 연산해야함
	// OperType 기준 오름차순 정렬
	// 정렬된대로 연산 진행
	
	UPROPERTY(VisibleAnywhere)
	bool bIsDead = false;
	
	FOnStatusEmpty OnCharacterDead;

private:
	UPROPERTY()
	TObjectPtr<UEquipment> Equipment;

	// 버프 계열 관리용 Map : ItemID - Func
	TMap<FString, FFunctionContext> BuffFunc;
	TQueue<FString> BuffReleaseQueue;

public:	
	UCharacterData();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Initialize(uint32 InLv, FCharacterDataRow& InData, UEquipment* InEquipment);

	inline bool TrySubtractStat(EStatus Type, uint32 Value) { return Stat[Type]->TrySubtract(Value); }
	inline void SubtractStat(EStatus Type, uint32 Value) { Stat[Type]->Subtract(Value); }
	
	void CheckIsDead(uint32 Max, uint32 Current);

	uint32 GetAttackPower(uint32 InBaseDamage);
	uint32 GetDefensePower();

	void AddBuff(FString& InItemID, FFunctionContext InContext);

private:
	void ApplyData(uint32 InLv, FCharacterDataRow& InData);
	void ApplyEquipment(UEquipment* InEquipment);
	void UpdateEquipment(EEquipType InType);

};
