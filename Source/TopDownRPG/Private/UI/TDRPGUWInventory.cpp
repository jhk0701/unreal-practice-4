// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWInventory.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "UI/TDRPGUWItemDetail.h"
#include "UI/TDRPGUWItemMenu.h"
#include "UI/TDRPGUWCanvas.h"

#include "Core/UIManager.h"
#include "Core/PlayerManager.h"
#include "Player/Inventory.h"

#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/UniformGridPanel.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

#include "TopDownRPG/TopDownRPG.h"


UTDRPGUWInventory::UTDRPGUWInventory()
{
	ConstructorHelpers::FClassFinder<UTDRPGUWItemMenu> TempMenu(TEXT("WidgetBlueprint'/Game/4-UI/WBP_TDRPGUWItemMenu.WBP_TDRPGUWItemMenu_C'"));
	ConstructorHelpers::FClassFinder<UTDRPGUWItemDetail> TempDetail(TEXT("WidgetBlueprint'/Game/4-UI/WBP_TDRPGUWItemDetail.WBP_TDRPGUWItemDetail_C'"));

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

void UTDRPGUWInventory::InitSubWidget()
{
	UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(GetParent());

	if (MenuWindowFactory && !MenuWindow)
	{
		MenuWindow = CreateWidget<UTDRPGUWItemMenu>(this, MenuWindowFactory);
		ParentCanvas->AddChildToCanvas(MenuWindow);

		if (UCanvasPanelSlot* WindowSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot))
		{
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
			WindowSlot->SetSize(DetailWindowSize);
			WindowSlot->SetPosition(FVector2D::ZeroVector);
		}

		HideItemDetail();
	}
}

void UTDRPGUWInventory::ShowItemDetail(UItemBase* InItem)
{
	DetailWindow->Open();
	DetailWindow->Update(InItem);
}

void UTDRPGUWInventory::HideItemDetail()
{
	DetailWindow->Close();
}

void UTDRPGUWInventory::ShowItemMenu(UItemBase* InItem)
{
	MenuWindow->Open();
	MenuWindow->Update(InItem);
}

void UTDRPGUWInventory::HideItemMenu()
{
	MenuWindow->Close();
}
