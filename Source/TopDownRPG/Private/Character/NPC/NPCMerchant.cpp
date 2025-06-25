// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/NPCMerchant.h"
#include "CommonConst.h"

#include "Core/UIManager.h"
#include "UI/UIMerchantUI.h"

#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/MerchantDataRow.h"

#include "Core/ItemFactory.h"
#include "Item/ItemBase.h"

#include "TopDownRPG/TopDownRPG.h"


ANPCMerchant::ANPCMerchant(){}

void ANPCMerchant::Interact()
{
	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();
	UUIMerchantUI* MerchantUI = UI->GetUI<UUIMerchantUI>();
	
	// 데이터 연결
	MerchantUI->SetMerchant(GetData());
	MerchantUI->Open();
}


FMerchantDataRow* ANPCMerchant::GetData()
{
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FMerchantDataRow* Data = GameData->GetRow<FMerchantDataRow>(ETableType::Merchant, MerchantID);
	return Data;
}
