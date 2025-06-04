// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumeItem.h"
#include "Data/ConsumeDataRow.h"

#include "TopDownRPG/TopDownRPG.h"

void UConsumeItem::Use()
{
	--Quantity;

	// 구조체는 다음과 같이 호출할 수 없음.
	// Cast는 UObject 기반 클래스에만 동작
	// Base가 실제로 하위 객체를 가리키고 있는 경우 static_cast<FConsumeDataRow*> 방식으로 호출 가능
	FConsumeDataRow* ConsumeData = static_cast<FConsumeDataRow*>(Data);
	if (!ConsumeData)
		return;

	// TODO : 아이템에 따른 효과 사용
	PRINT_LOG(TEXT("Consume Item Called [%s]"), *ConsumeData->ItemName.ToString());
}

void UConsumeItem::OnDurationEnded()
{

}

void UConsumeItem::InvokeSlot()
{
	Use();
}
