// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWMerchantUI.h"

#include "CommonConst.h"
#include "TDRPGEnum.h"
#include "Character/NPC/NPCMerchant.h"
#include "Data/MerchantDataRow.h"
#include "Data/InnerStringArray.h"

#include "Core/UIManager.h"
#include "UI/TDRPGUWPlayerUI.h"
#include "UI/TDRPGUWInventory.h"
#include "UI/Element/TDRPGUWProductSlot.h"

#include <Components/Button.h>
#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>


void UTDRPGUWMerchantUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWMerchantUI::Close);
}

void UTDRPGUWMerchantUI::Open()
{
	UUIManager* UI = GetGameInstance()->GetSubsystem<UUIManager>();
	UI->GetUI<UTDRPGUWPlayerUI>()->Inventory->Open();

	Super::Open();
}

void UTDRPGUWMerchantUI::Close()
{
	Clear();

	Super::Close();
}

void UTDRPGUWMerchantUI::SetMerchant(ANPCMerchant* InMerchant)
{
	if (!InMerchant)
		return;

	Merchant = InMerchant;

	// 받은 데이터로 UI 생성
	auto& ProductMap = Merchant->GetData()->ProductID;

	TArray<ETableType> Keys;
	ProductMap.GetKeys(Keys);

	int32 KeyCnt = Keys.Num();
	int32 Index = 0;
	for (int32 i = 0; i < KeyCnt; ++i)
	{
		for (FString& Product : ProductMap[Keys[i]].Array)
		{
			InitProductSlot(Product, Keys[i], Index);
			++Index;
		}
	}
}

void UTDRPGUWMerchantUI::InitProductSlot(const FString& InProductID, const ETableType InType, const int32 InIndex)
{
	UTDRPGUWProductSlot* SlotInst;

	if (ProductSlotPool.IsEmpty())
		SlotInst = CreateProductSlot();
	else
		ProductSlotPool.Dequeue(SlotInst);

	ActiveProductSlot.Enqueue(SlotInst);
	SlotInst->SetVisibility(ESlateVisibility::Visible);

	if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(SlotInst->Slot)) 
	{
		int32 Row = InIndex / RowSize;
		int32 Column = InIndex % RowSize;

		GridSlot->SetRow(Row);
		GridSlot->SetColumn(Column);
	}

	SlotInst->Bind(InProductID, InType);
	SlotInst->OnButtonClicked.AddUObject(this, &UTDRPGUWMerchantUI::OnSlotClicked);
}

UTDRPGUWProductSlot* UTDRPGUWMerchantUI::CreateProductSlot()
{
	if (!ProductSlotFactory)
		return nullptr;

	UTDRPGUWProductSlot* SlotInst = CreateWidget<UTDRPGUWProductSlot>(this, ProductSlotFactory);
	MerchantSideContainer->AddChild(SlotInst);

	if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(SlotInst->Slot))
	{
		GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	}

	return SlotInst;
}

void UTDRPGUWMerchantUI::Clear()
{
	while (!ActiveProductSlot.IsEmpty()) 
	{
		UTDRPGUWProductSlot* SlotInst;
		ActiveProductSlot.Dequeue(SlotInst);
		ProductSlotPool.Enqueue(SlotInst);

		SlotInst->SetVisibility(ESlateVisibility::Hidden);
		SlotInst->OnButtonClicked.Clear();
	}
}


void UTDRPGUWMerchantUI::OnSlotClicked(UTDRPGUWSlotBase* InSlot)
{
	// TODO : 세부 메뉴 팝업으로 바꾸기
	UTDRPGUWProductSlot* ClickedSlot = Cast<UTDRPGUWProductSlot>(InSlot);
	check(ClickedSlot);

	FString ID;
	ETableType Type;
	ClickedSlot->GetProduct(ID, Type);

	check(ID != CommonConst::EMPTY_ITEM_ID);

	// Buy
	OnClickBuy(ID, Type);
}

void UTDRPGUWMerchantUI::OnClickBuy(const FString& InProductID, const ETableType InType)
{
	// 유저가 구매 버튼을 누름 -> 상인의 아이템 판매
	Merchant->BuyItem(InProductID, InType);
}
