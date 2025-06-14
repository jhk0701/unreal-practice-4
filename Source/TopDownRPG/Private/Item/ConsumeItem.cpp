// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumeItem.h"
#include "Item/Function/ItemFuncBase.h"
#include "Data/ConsumeDataRow.h"

#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"

#include "TopDownRPG/TopDownRPG.h"

void UConsumeItem::Use(AActor* Subject)
{
	// TODO : 아이템 쿨타임 적용

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
	
	// 0초라면 즉시 사용
	// 1초 이상이라면 지속시간
	if(ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Subject))
	{
		// 효과 객체로부터 맥락 구조체 생성
		TSharedPtr<FFunctionContext> Context = ConsumeData->Function->GetContext(ConsumeData->Value, ConsumeData->Duration);

		// 아이템에서 대상 캐릭터에게 효과 객체 적용
		Player->DataComp->AddBuff(*ItemID, Context);
	}
}


void UConsumeItem::InvokeSlot(AActor* Subject)
{
	// 더 필요사항이 많아지면 Context 구조체로 만들어서 사용할 것
	Use(Subject);
}
