// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "EquipmentItem.generated.h"


/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UEquipmentItem : public UItemBase
{
	GENERATED_BODY()
	
	// 장비류는 장착 시 능력을 향상
	// 최종 공격력 상승 : 무기 , 최종 방어력 상승 : 방어
	// 장착 시, 추가 효과 제공

public:
	virtual FItemDataRow* GetData() override;

	// 아이템 활용
	void Equip();
	void Unequip();
};
