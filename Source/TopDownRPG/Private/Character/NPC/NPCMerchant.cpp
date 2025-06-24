// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/NPCMerchant.h"
#include "CommonConst.h"

#include "Core/UIManager.h"
#include "UI/TDRPGUWMerchantUI.h"

#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/MerchantDataRow.h"

#include "Core/ItemFactory.h"
#include "Item/ItemBase.h"

#include "TopDownRPG/TopDownRPG.h"


ANPCMerchant::ANPCMerchant(){}

void ANPCMerchant::BeginPlay()
{
	Super::BeginPlay();		
		
	InitMerchant();
}

void ANPCMerchant::Interact()
{
	PRINT_LOG(TEXT("NPC Merchant Interact"));

	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();

	UTDRPGUWMerchantUI* MerchantUI = UI->GetUI<UTDRPGUWMerchantUI>();
	
	MerchantUI->BindData();
	// 데이터 연결
	MerchantUI->Open();
}

void ANPCMerchant::InitMerchant()
{
	// TODO : 취급 데이터 받아오기
	// Data->IngredientID

}

FMerchantDataRow* ANPCMerchant::GetData()
{
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FMerchantDataRow* Data = GameData->GetRow<FMerchantDataRow>(ETableType::Merchant, MerchantID);
	return Data;
}
