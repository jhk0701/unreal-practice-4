// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Equipment.generated.h"

class UEquipmentItem;
enum class EEquipType : uint8;
enum class EAbility : uint8;
enum class EStatus : uint8;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipmentUpdated, EEquipType);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UEquipment : public UObject
{
	GENERATED_BODY()

public:
	FOnEquipmentUpdated OnEquipmentUpdated;

private:
	UPROPERTY()
	TMap<EEquipType, UEquipmentItem*> Equipment;

	// 공통요소 합산
	int32 AddictiveAttack;
	int32 AddictiveDefense;
	TMap<EStatus, int32> AddictiveStatus;
	TMap<EAbility, int32> AddictiveAbility;
	
public:
	UEquipment();
	inline UEquipmentItem* GetEquipment(EEquipType InType) const { return Equipment[InType]; }

	// 장착, 장착 해제
	void Equip(EEquipType InType, UEquipmentItem* InItem);
	void Unequip(EEquipType InType);

	// 합계 요소 getter
	inline const int32 GetAddictiveAttack() { return AddictiveAttack; }
	inline const int32 GetAddictiveDefense() { return AddictiveDefense; }

private:
	void ApplyEquipment(EEquipType InType);
	void UnapplyEquipment(EEquipType InType);
};
