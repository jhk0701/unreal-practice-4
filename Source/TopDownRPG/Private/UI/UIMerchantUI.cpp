// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIMerchantUI.h"

#include "TDRPGEnum.h"
#include "Data/MerchantDataRow.h"
#include "Data/InnerStringArray.h"

#include "UI/Element/UIProductSlot.h"

#include <Components/Button.h>
#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>


void UUIMerchantUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UUIBase::Close);
}

void UUIMerchantUI::SetMerchant(FMerchantDataRow* InMerchantData)
{
	if (!InMerchantData)
		return;

	// InMerchantData->ProductID
	// 받은 데이터로 UI 생성
	auto& ProductMap = InMerchantData->ProductID;

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

void UUIMerchantUI::InitProductSlot(FString& InProductID, ETableType InType, int32 InIndex)
{
	UUIProductSlot* SlotInst = CreateProductSlot();

	if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(SlotInst->Slot)) 
	{
		int32 Row = InIndex / RowSize;
		int32 Column = InIndex % RowSize;

		GridSlot->SetRow(Row);
		GridSlot->SetColumn(Column);
	}

	SlotInst->Bind(InProductID, InType);
}

UUIProductSlot* UUIMerchantUI::CreateProductSlot()
{
	if (!ProductSlotFactory)
		return nullptr;

	UUIProductSlot* SlotInst = CreateWidget<UUIProductSlot>(this, ProductSlotFactory);
	MerchantSideContainer->AddChild(SlotInst);

	if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(SlotInst->Slot))
	{
		GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	}

	return SlotInst;
}
