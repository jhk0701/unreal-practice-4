// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIEquipment.h"
#include "UI/Element/UIInventorySlot.h"
#include "UI/UIEquipmentMenu.h"

#include "TDRPGEnum.h"

#include "Player/Equipment.h"
#include "Item/EquipmentItem.h"

#include <Components/VerticalBox.h>
#include <Components/Button.h>
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>


UUIEquipment::UUIEquipment()
{
	ConstructorHelpers::FClassFinder<UUIEquipmentMenu> TempMenu(TEXT("WidgetBlueprint'/Game/4-UI/SubWBP_EquipmentMenu.SubWBP_EquipmentMenu_C'"));
	if (TempMenu.Succeeded())
		MenuWindowFactory = TempMenu.Class;
}

void UUIEquipment::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UUIBase::Close);

	Slots.Empty();

	if (SlotContainer) 
	{
		int32 Cnt = SlotContainer->GetChildrenCount();
		for (int32 i = 0; i < Cnt; ++i) 
		{
			if (UUIInventorySlot* SlotInst = Cast<UUIInventorySlot>(SlotContainer->GetChildAt(i)))
			{
				EEquipType Type = (EEquipType)i;

				Slots.Add(Type, SlotInst);

				Slots[Type]->OnButtonClicked.AddUObject(this, &UUIEquipment::ShowMenu);
			}
		}
	}

	// Sub UI 생성
	if (!MenuWindow && MenuWindowFactory) 
	{
		MenuWindow = CreateWidget<UUIEquipmentMenu>(this, MenuWindowFactory);

		UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(GetParent());
		ParentCanvas->AddChildToCanvas(MenuWindow);

		if (UCanvasPanelSlot* WindowSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot))
		{
			WindowSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			WindowSlot->SetAlignment(FVector2D::ZeroVector);

			WindowSlot->SetSize(MenuWindow->Size);
			WindowSlot->SetPosition(FVector2D::ZeroVector);
		}

		HideMenu();
	}
}

void UUIEquipment::Close()
{
	Super::Close();

	HideMenu();
}

void UUIEquipment::Bind(UEquipment* InEquipment)
{
	BindedEquipment = InEquipment;
	BindedEquipment->OnEquipmentUpdated.AddUObject(this, &UUIEquipment::UpdateSlot);

	uint8 Cnt = (uint8)EEquipType::COUNT;
	for (uint8 i = 0; i < Cnt; ++i) 
		UpdateSlot((EEquipType)i);
}

void UUIEquipment::UpdateSlot(EEquipType InEquipType)
{
	if (UItemBase* Item = BindedEquipment->GetEquipment(InEquipType))
		Slots[InEquipType]->Bind(Item);
	else
		Slots[InEquipType]->Clear();
}

void UUIEquipment::ShowMenu(UUISlotBase* InSlot)
{
	UCanvasPanelSlot* EquipmentSlot = Cast<UCanvasPanelSlot>(Slot);
	UCanvasPanelSlot* MenuSlot = Cast<UCanvasPanelSlot>(MenuWindow->Slot);
	if (EquipmentSlot && MenuSlot)
	{
		FVector2D Pos = EquipmentSlot->GetPosition();
		FVector2D Size = EquipmentSlot->GetSize();
		Pos.X += Size.X;

		MenuSlot->SetPosition(Pos);
	}

	MenuWindow->Open();
	if(UUIInventorySlot* ItemSlot = Cast<UUIInventorySlot>(InSlot))
		MenuWindow->Update(ItemSlot->GetBindedItem());
}

void UUIEquipment::HideMenu()
{
	MenuWindow->Close();
}