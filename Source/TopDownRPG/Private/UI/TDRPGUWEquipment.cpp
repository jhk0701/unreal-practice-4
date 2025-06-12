// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWEquipment.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "TDRPGEnum.h"

#include "Core/PlayerManager.h"
#include "Player/Equipment.h"
#include "Item/EquipmentItem.h"

#include <Components/VerticalBox.h>
#include <Components/Button.h>


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
			}
		}
	}

	UPlayerManager* PlayerManager = GetGameInstance()->GetSubsystem<UPlayerManager>();
	BindedEquipment = PlayerManager->Equipment;
	BindedEquipment->OnEquipmentChanged.AddUObject(this, &UTDRPGUWEquipment::UpdateSlot);
}

void UTDRPGUWEquipment::UpdateSlot(EEquipType InEquipType)
{
	if (UItemBase* Item = BindedEquipment->Equipment[InEquipType])
		Slots[InEquipType]->SetData(Item);
	else
		Slots[InEquipType]->Clear();
}
