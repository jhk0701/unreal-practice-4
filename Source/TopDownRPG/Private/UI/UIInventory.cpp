// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIInventory.h"
#include "UI/Element/UIInventorySlot.h"
#include "UI/UIItemDetail.h"
#include "UI/UIInventoryMenu.h"
#include "UI/UICanvas.h"

#include "Core/UIManager.h"
#include "Core/PlayerManager.h"
#include "Player/Inventory.h"

#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

#include "TopDownRPG/TopDownRPG.h"


UUIInventory::UUIInventory()
{
	ConstructorHelpers::FClassFinder<UUIInventoryMenu> TempMenu(TEXT("WidgetBlueprint'/Game/4-UI/SubWBP_InventoryMenu.SubWBP_InventoryMenu_C'"));
	if (TempMenu.Succeeded())
		MenuWindowFactory = TempMenu.Class;

	ConstructorHelpers::FClassFinder<UUIItemDetail> TempDetail(TEXT("WidgetBlueprint'/Game/4-UI/SubWBP_ItemDetail.SubWBP_ItemDetail_C'"));
	if (TempDetail.Succeeded())
		DetailWindowFactory = TempDetail.Class;
}

void UUIInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitSubWidget();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UUIBase::Close);

	int32 SlotCnt = SlotContainer->GetChildrenCount();

	// TODO : 동적으로 생성하기
	Slots.Empty();
	Slots.Init(nullptr, SlotCnt);
	
	for (int32 i = 0; i < SlotCnt; ++i)
	{
		UUIInventorySlot* SlotInst = Cast<UUIInventorySlot>(SlotContainer->GetChildAt(i));
		
		// 슬롯 마우스 호버링 이벤트들 등록
		SlotInst->OnCursorEnter.AddUObject(this, &UUIInventory::ShowItemDetail);
		SlotInst->OnCursorLeave.AddUObject(this, &UUIInventory::HideItemDetail);
		
		// 아이템 슬롯 클릭 시, 아이템 상호작용 메뉴 추가
		SlotInst->OnButtonClicked.AddUObject(this, &UUIInventory::ShowItemMenu);

		if (SlotInst) 
			Slots[i] = SlotInst;
	}
}

void UUIInventory::Close()
{
	HideItemDetail();
	HideItemMenu();

	Super::Close();
}

void UUIInventory::Bind(UPlayerManager* InManager)
{
	// 플레이어 데이터 받아오기
	BindedInventory = InManager->Inventory;

	// 1. 골드
	InManager->CurrencyGold->OnValueChanged.AddUObject(this, &UUIInventory::UpdateGold);
	UpdateGold(InManager->CurrencyGold->GetCurrency());

	// 2. 인벤토리 정보 연동
	int32 SlotCnt = SlotContainer->GetChildrenCount();
	for (int32 i = 0; i < SlotCnt; ++i)
		Slots[i]->Bind(BindedInventory->Items[i]);

	BindedInventory->OnInventoryUpdated.AddUObject(this, &UUIInventory::UpdateInventory);
}

void UUIInventory::UpdateInventory(uint8 Index)
{
	Slots[Index]->Clear();
	Slots[Index]->Bind(BindedInventory->Items[Index]);
}

void UUIInventory::UpdateGold(uint32 Gold)
{
	GoldLabel->SetText(FText::FromString(FString::Printf(TEXT("%u G"), Gold)));
}

void UUIInventory::InitSubWidget()
{
	// TODO : 리팩토링 해볼 것
	UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(GetParent());

	if (MenuWindowFactory && !MenuWindow)
	{
		MenuWindow = CreateWidget<UUIInventoryMenu>(this, MenuWindowFactory);
		ParentCanvas->AddChildToCanvas(MenuWindow);

		if (UCanvasPanelSlot* WindowSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot))
		{
			WindowSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			WindowSlot->SetAlignment(FVector2D::ZeroVector);

			WindowSlot->SetSize(MenuWindow->Size);
			WindowSlot->SetPosition(FVector2D::ZeroVector);	
		}

		HideItemMenu();
	}

	if (DetailWindowFactory && !DetailWindow)
	{
		DetailWindow = CreateWidget<UUIItemDetail>(this, DetailWindowFactory);
		ParentCanvas->AddChildToCanvas(DetailWindow);

		if (UCanvasPanelSlot* WindowSlot = Cast<UCanvasPanelSlot>(DetailWindow->Slot))
		{
			WindowSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			WindowSlot->SetAlignment(FVector2D::ZeroVector);

			WindowSlot->SetSize(DetailWindow->Size);
			WindowSlot->SetPosition(FVector2D::ZeroVector);
		}

		HideItemDetail();
	}
}

void UUIInventory::ShowItemDetail(UUISlotBase* InSlot)
{
	UCanvasPanelSlot* InvenCanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	UCanvasPanelSlot* DetailSlot = Cast<UCanvasPanelSlot>(DetailWindow->Slot);
	if (InvenCanvasSlot && DetailSlot)
	{
		FVector2D Pos = InvenCanvasSlot->GetPosition();
		Pos.X -= DetailWindow->Size.X;
		DetailSlot->SetPosition(Pos);
	}

	DetailWindow->Open();

	if(UUIInventorySlot* ItemSlot = Cast<UUIInventorySlot>(InSlot))
		DetailWindow->Update(ItemSlot->GetBindedItem());
}

void UUIInventory::HideItemDetail()
{
	DetailWindow->Close();
}

void UUIInventory::ShowItemMenu(UUISlotBase* InSlot)
{
	UCanvasPanelSlot* InvenCanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	UCanvasPanelSlot* MenuSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot);
	if (InvenCanvasSlot && MenuSlot)
	{
		FVector2D Pos = InvenCanvasSlot->GetPosition();
		Pos.X -= MenuWindow->Size.X;
		Pos.Y += DetailWindow->Size.Y;
		MenuSlot->SetPosition(Pos);
	}

	MenuWindow->Open();

	if (UUIInventorySlot* ItemSlot = Cast<UUIInventorySlot>(InSlot))
		MenuWindow->Update(ItemSlot->GetBindedItem());
}

void UUIInventory::HideItemMenu()
{
	MenuWindow->Close();
}
