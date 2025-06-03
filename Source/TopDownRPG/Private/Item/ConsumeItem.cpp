// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumeItem.h"

void UConsumeItem::Use()
{
	--Quantity;

	// 아이템에 따른 효과 사용
	// 하위 객체들에서 구현
}
