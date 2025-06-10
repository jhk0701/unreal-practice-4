// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWInventory.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "UI/TDRPGUWItemDetail.h"

#include "Core/PlayerManager.h"
#include "Player/Inventory.h"

#include <Components/UniformGridPanel.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>


void UTDRPGUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);
	HideItemDetail();

	int32 SlotCnt = SlotContainer->GetChildrenCount();

	// TODO : 동적으로 생성하기
	Slots.Empty();
	Slots.Init(nullptr, SlotCnt);
	
	for (int32 i = 0; i < SlotCnt; ++i)
	{
		UTDRPGUWSlotBase* SlotInst = Cast<UTDRPGUWSlotBase>(SlotContainer->GetChildAt(i));
		
		// 슬롯 마우스 호버링 이벤트들 등록
		SlotInst->OnMouseEnterEvent.AddUObject(this, &UTDRPGUWInventory::ShowItemDetail);
		SlotInst->OnMouseLeaveEvent.AddUObject(this, &UTDRPGUWInventory::HideItemDetail);

		if (SlotInst) 
			Slots[i] = SlotInst;
	}

	// 플레이어 데이터 받아오기
	UPlayerManager* PlayerManager = GetGameInstance()->GetSubsystem<UPlayerManager>();
	if (!PlayerManager)
		return;

	UInventory* Inventory = PlayerManager->Inventory;

	// 1. 골드
	PlayerManager->CurrencyGold->OnValueChanged.AddUObject(this, &UTDRPGUWInventory::UpdateGold);
	UpdateGold(PlayerManager->CurrencyGold->GetCurrency());
	
	// 2. 인벤토리 정보 연동
	for (int32 i = 0; i < SlotCnt; ++i) 
		Slots[i]->SetData(Inventory->Items[i]);
}

void UTDRPGUWInventory::UpdateGold(uint32 Gold)
{
	GoldLabel->SetText(FText::FromString(FString::Printf(TEXT("%u G"), Gold)));
}

void UTDRPGUWInventory::ShowItemDetail(UItemBase* InItem)
{
	DetailWindow->SetVisibility(ESlateVisibility::Visible);
	DetailWindow->Update(InItem);
}

void UTDRPGUWInventory::HideItemDetail()
{
	DetailWindow->SetVisibility(ESlateVisibility::Hidden);
}
