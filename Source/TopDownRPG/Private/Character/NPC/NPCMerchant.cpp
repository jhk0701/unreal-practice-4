// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/NPCMerchant.h"

#include "Core/UIManager.h"
#include "UI/TDRPGUWMerchantUI.h"

#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/MerchantDataRow.h"

#include "Core/PlayerManager.h"
#include "Player/Inventory.h"

#include "Core/ItemFactory.h"
#include "Data/ItemDataRow.h"
#include "Item/ItemBase.h"

#include "TopDownRPG/TopDownRPG.h"


ANPCMerchant::ANPCMerchant(){}

void ANPCMerchant::Interact()
{
	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();
	UTDRPGUWMerchantUI* MerchantUI = UI->GetUI<UTDRPGUWMerchantUI>();
	
	// 데이터 연결
	MerchantUI->SetMerchant(this);
	MerchantUI->Open();
}


FMerchantDataRow* ANPCMerchant::GetData()
{
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FMerchantDataRow* Data = GameData->GetRow<FMerchantDataRow>(ETableType::Merchant, MerchantID);
	return Data;
}

void ANPCMerchant::BuyItem(const FString& InProductID, const ETableType& InType, const uint8& InQuantity)
{
	UItemFactory* ItemFactory = GetGameInstance()->GetSubsystem<UItemFactory>();
	UItemBase* ItemToSell = ItemFactory->GetItem(InType, InProductID);

	uint32 Price = ItemToSell->GetData()->Price;
	Price = GetDiscountedPrice(Price);

	UPlayerManager* Player = GetGameInstance()->GetSubsystem<UPlayerManager>();

	// 가격 지불
	if (Player->CurrencyGold->SafeSub(Price)) 
	{
		// 아이템 지급
		Player->Inventory->AddItem(ItemToSell);
	}
	else
	{
		// 금액 부족
		// TODO : 메시지 띄울것
		PRINT_LOG(TEXT("Not Enough Gold"));
	}
}

uint32 ANPCMerchant::GetDiscountedPrice(uint32& InPrice)
{
	float Discount = GetData()->Discount;
	return InPrice * (1.0f - Discount * 0.01f);
}
