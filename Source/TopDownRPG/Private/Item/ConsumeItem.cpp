// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumeItem.h"
#include "Data/ConsumeDataRow.h"
#include "Item/Function/ItemFuncBase.h"

#include "TopDownRPG/TopDownRPG.h"

void UConsumeItem::Use(AActor* Subject)
{
	if (Quantity == 0)
		return;

	--Quantity;
	// TODO: 남은 아이템을 다 썼을 때 후속조치

	// 구조체는 다음과 같이 호출할 수 없음.
	// Cast는 UObject 기반 클래스에만 동작
	// Base가 실제로 하위 객체를 가리키고 있는 경우 static_cast<FConsumeDataRow*> 방식으로 호출 가능
	FConsumeDataRow* ConsumeData = static_cast<FConsumeDataRow*>(Data);
	if (!ConsumeData)
		return;

	PRINT_LOG(TEXT("Consume Item Called [%s] (%u)"), *ConsumeData->ItemName.ToString(), Quantity);
	
	// TODO : 아이템 쿨타임
	// TODO : 아이템 지속 시간 기능
	ConsumeData->Function->Activate(Subject, ConsumeData->Value);
}

void UConsumeItem::OnDurationEnded()
{

}

void UConsumeItem::InvokeSlot(AActor* Subject)
{
	// TODO : 더 필요사항이 많아지면 Context 구조체로 만들어서 사용할 것
	Use(Subject);
}
