// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ItemFactory.h"

#include "TDRPGEnum.h"
#include "Item/ItemBase.h"
#include "Item/ConsumeItem.h"
#include "Item/EquipmentItem.h"
#include "Item/WeaponItem.h"

//void UItemFactory::Test()
//{
//	UGameInstance* GameInst = GetGameInstance();
//
//	// 테스트용 일반 아이템
//	UItemBase* TestIngre_1 = NewObject<UItemBase>();
//	UItemBase* TestIngre_2 = NewObject<UItemBase>();
//	UItemBase* TestIngre_3 = NewObject<UItemBase>();
//
//	TestIngre_1->Initialize(TEXT("0001"), GameInst, 5);
//	TestIngre_2->Initialize(TEXT("0002"), GameInst, 10);
//	TestIngre_3->Initialize(TEXT("0003"), GameInst, 20);
//
//	/*
//	Inventory->AddItem(TestIngre_1);
//	Inventory->AddItem(TestIngre_2);
//	Inventory->AddItem(TestIngre_3);
//	*/
//
//	// 테스트용 소비 아이템
//	UConsumeItem* TestConsume = NewObject<UConsumeItem>();
//	TestConsume->Initialize(TEXT("0001"), GameInst, 30);
//
//	// Inventory->AddItem(TestConsume);
//
//	// 테스트용 장비 아이템 지급
//	UEquipmentItem* TestEquip = NewObject<UEquipmentItem>();
//	TestEquip->Initialize(TEXT("0001"), GameInst, 1);
//
//	// Inventory->AddItem(TestEquip);
//
//	// 테스트용 무기 아이템 지급
//	UWeaponItem* TestWeapon = NewObject<UWeaponItem>();
//	TestWeapon->Initialize(TEXT("0001"), GameInst, 1);
//
//	// Inventory->AddItem(TestWeapon);
//}

UItemBase* UItemFactory::GetItem(ETableType ItemType, const FString& InItemID, uint32 InQuantity)
{
	if (InItemID == CommonConst::EMPTY_ITEM_ID)
		return nullptr;

	UItemBase* Result = nullptr;

	switch (ItemType)
	{
	case ETableType::Weapon:
		Result = GetItem<UWeaponItem>(InItemID, InQuantity);
		break;
	case ETableType::Equipment:
		Result = GetItem<UEquipmentItem>(InItemID, InQuantity);
		break;
	case ETableType::Consume:
		Result = GetItem<UConsumeItem>(InItemID, InQuantity);
		break;
	case ETableType::Ingredient:
		Result = GetItem<UItemBase>(InItemID, InQuantity);
		break;
	}

	return Result;
}
