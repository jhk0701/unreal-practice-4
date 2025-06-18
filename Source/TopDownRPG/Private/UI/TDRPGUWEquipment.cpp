// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWEquipment.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "UI/TDRPGUWEquipmentMenu.h"

#include "TDRPGEnum.h"

#include "Player/Equipment.h"
#include "Item/EquipmentItem.h"

#include <Components/VerticalBox.h>
#include <Components/Button.h>
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>



UTDRPGUWEquipment::UTDRPGUWEquipment()
{
	ConstructorHelpers::FClassFinder<UTDRPGUWEquipmentMenu> TempMenu(TEXT("WidgetBlueprint'/Game/4-UI/WBP_TDRPGUWEquipmentMenu.WBP_TDRPGUWEquipmentMenu_C'"));
	if (TempMenu.Succeeded())
		MenuWindowFactory = TempMenu.Class;
}

void UTDRPGUWEquipment::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);

	Slots.Empty();

	if (SlotContainer) 
	{
		int32 Cnt = SlotContainer->GetChildrenCount();
		for (int32 i = 0; i < Cnt; ++i) 
		{
			if (UTDRPGUWSlotBase* SlotInst = Cast<UTDRPGUWSlotBase>(SlotContainer->GetChildAt(i)))
			{
				EEquipType Type = (EEquipType)i;

				Slots.Add(Type, SlotInst);

				Slots[Type]->OnButtonClicked.AddUObject(this, &UTDRPGUWEquipment::ShowMenu);
			}
		}
	}

	// Sub UI 생성
	if (!MenuWindow && MenuWindowFactory) 
	{
		MenuWindow = CreateWidget<UTDRPGUWEquipmentMenu>(this, MenuWindowFactory);

		UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(GetParent());
		ParentCanvas->AddChildToCanvas(MenuWindow);

		if (UCanvasPanelSlot* WindowSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot))
		{
			WindowSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			WindowSlot->SetAlignment(FVector2D::ZeroVector);

			WindowSlot->SetSize(MenuWindowSize);
			WindowSlot->SetPosition(FVector2D::ZeroVector);
		}

		HideMenu();
	}
}

void UTDRPGUWEquipment::Bind(UEquipment* InEquipment)
{
	BindedEquipment = InEquipment;
	BindedEquipment->OnEquipmentUpdated.AddUObject(this, &UTDRPGUWEquipment::UpdateSlot);

	uint8 Cnt = (uint8)EEquipType::COUNT;
	for (uint8 i = 0; i < Cnt; ++i) 
		UpdateSlot((EEquipType)i);
}

void UTDRPGUWEquipment::UpdateSlot(EEquipType InEquipType)
{
	if (UItemBase* Item = BindedEquipment->Equipment[InEquipType])
		Slots[InEquipType]->Bind(Item);
	else
		Slots[InEquipType]->Clear();
}

void UTDRPGUWEquipment::ShowMenu(UTDRPGUWSlotBase* InSlot)
{
	UCanvasPanelSlot* EquipmentSlot = Cast<UCanvasPanelSlot>(Slot);
	UCanvasPanelSlot* MenuSlot = Cast<UCanvasPanelSlot>(MenuWindow);
	if (EquipmentSlot && MenuSlot)
	{
		FVector2D Size = EquipmentSlot->GetSize();
		FVector2D Pos = EquipmentSlot->GetPosition();
		Pos.X += Size.X;
		MenuSlot->SetPosition(Pos);
	}

	MenuWindow->Open();
	MenuWindow->Update(InSlot->GetBindedItem());
}

void UTDRPGUWEquipment::HideMenu()
{
	MenuWindow->Close();
}