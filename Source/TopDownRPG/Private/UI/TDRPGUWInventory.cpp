// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWInventory.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "UI/TDRPGUWItemDetail.h"
#include "UI/TDRPGUWInventoryMenu.h"
#include "UI/TDRPGUWCanvas.h"

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


UTDRPGUWInventory::UTDRPGUWInventory()
{
	ConstructorHelpers::FClassFinder<UTDRPGUWInventoryMenu> TempMenu(TEXT("WidgetBlueprint'/Game/4-UI/WBP_InventoryMenu.WBP_InventoryMenu_C'"));
	ConstructorHelpers::FClassFinder<UTDRPGUWItemDetail> TempDetail(TEXT("WidgetBlueprint'/Game/4-UI/WBP_ItemDetail.WBP_ItemDetail_C'"));

	if (TempMenu.Succeeded())
		MenuWindowFactory = TempMenu.Class;

	if (TempDetail.Succeeded())
		DetailWindowFactory = TempDetail.Class;
}

void UTDRPGUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitSubWidget();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);

	int32 SlotCnt = SlotContainer->GetChildrenCount();

	// TODO : 동적으로 생성하기
	Slots.Empty();
	Slots.Init(nullptr, SlotCnt);
	
	for (int32 i = 0; i < SlotCnt; ++i)
	{
		UTDRPGUWSlotBase* SlotInst = Cast<UTDRPGUWSlotBase>(SlotContainer->GetChildAt(i));
		
		// 슬롯 마우스 호버링 이벤트들 등록
		SlotInst->OnCursorEnter.AddUObject(this, &UTDRPGUWInventory::ShowItemDetail);
		SlotInst->OnCursorLeave.AddUObject(this, &UTDRPGUWInventory::HideItemDetail);
		
		// 아이템 슬롯 클릭 시, 아이템 상호작용 메뉴 추가
		SlotInst->OnButtonClicked.AddUObject(this, &UTDRPGUWInventory::ShowItemMenu);

		if (SlotInst) 
			Slots[i] = SlotInst;
	}
}

void UTDRPGUWInventory::Close()
{
	HideItemDetail();
	HideItemMenu();

	Super::Close();
}

void UTDRPGUWInventory::Bind(UPlayerManager* InManager)
{
	// 플레이어 데이터 받아오기
	BindedInventory = InManager->Inventory;

	// 1. 골드
	InManager->CurrencyGold->OnValueChanged.AddUObject(this, &UTDRPGUWInventory::UpdateGold);
	UpdateGold(InManager->CurrencyGold->GetCurrency());

	// 2. 인벤토리 정보 연동
	int32 SlotCnt = SlotContainer->GetChildrenCount();
	for (int32 i = 0; i < SlotCnt; ++i)
		Slots[i]->Bind(BindedInventory->Items[i]);

	BindedInventory->OnInventoryUpdated.AddUObject(this, &UTDRPGUWInventory::UpdateInventory);
}

void UTDRPGUWInventory::UpdateInventory(uint8 Index)
{
	Slots[Index]->Clear();
	Slots[Index]->Bind(BindedInventory->Items[Index]);
}

void UTDRPGUWInventory::UpdateGold(uint32 Gold)
{
	GoldLabel->SetText(FText::FromString(FString::Printf(TEXT("%u G"), Gold)));
}

void UTDRPGUWInventory::InitSubWidget()
{
	// TODO : 리팩토링 해볼 것
	UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(GetParent());

	if (MenuWindowFactory && !MenuWindow)
	{
		MenuWindow = CreateWidget<UTDRPGUWInventoryMenu>(this, MenuWindowFactory);
		ParentCanvas->AddChildToCanvas(MenuWindow);

		if (UCanvasPanelSlot* WindowSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot))
		{
			WindowSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			WindowSlot->SetAlignment(FVector2D::ZeroVector);

			WindowSlot->SetSize(MenuWindowSize);
			WindowSlot->SetPosition(FVector2D::ZeroVector);	
		}

		HideItemMenu();
	}

	if (DetailWindowFactory && !DetailWindow)
	{
		DetailWindow = CreateWidget<UTDRPGUWItemDetail>(this, DetailWindowFactory);
		ParentCanvas->AddChildToCanvas(DetailWindow);

		if (UCanvasPanelSlot* WindowSlot = Cast<UCanvasPanelSlot>(DetailWindow->Slot))
		{
			WindowSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			WindowSlot->SetAlignment(FVector2D::ZeroVector);

			WindowSlot->SetSize(DetailWindowSize);
			WindowSlot->SetPosition(FVector2D::ZeroVector);
		}

		HideItemDetail();
	}
}

void UTDRPGUWInventory::ShowItemDetail(UTDRPGUWSlotBase* InSlot)
{
	UCanvasPanelSlot* InvenCanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	UCanvasPanelSlot* DetailSlot = Cast<UCanvasPanelSlot>(DetailWindow->Slot);
	if (InvenCanvasSlot && DetailSlot)
	{
		FVector2D Pos = InvenCanvasSlot->GetPosition();
		Pos.X -= DetailWindowSize.X;
		DetailSlot->SetPosition(Pos);
	}

	DetailWindow->Open();
	DetailWindow->Update(InSlot->GetBindedItem());
}

void UTDRPGUWInventory::HideItemDetail()
{
	DetailWindow->Close();
}

void UTDRPGUWInventory::ShowItemMenu(UTDRPGUWSlotBase* InSlot)
{
	UCanvasPanelSlot* InvenCanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	UCanvasPanelSlot* MenuSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot);
	if (InvenCanvasSlot && MenuSlot)
	{
		FVector2D Pos = InvenCanvasSlot->GetPosition();
		Pos.X -= MenuWindowSize.X;
		Pos.Y += DetailWindowSize.Y;
		MenuSlot->SetPosition(Pos);
	}

	MenuWindow->Open();
	MenuWindow->Update(InSlot->GetBindedItem());
}

void UTDRPGUWInventory::HideItemMenu()
{
	MenuWindow->Close();
}
