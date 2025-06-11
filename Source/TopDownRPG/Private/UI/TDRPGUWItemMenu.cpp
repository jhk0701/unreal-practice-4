// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWItemMenu.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>

#include "Core/PlayerManager.h"
#include "Player/QuickSlot.h"

#include "Item/ConsumeItem.h"
#include "Item/EquipmentItem.h"
#include "Item/IngredientItem.h"

#include "TopDownRPG/TopDownRPG.h"

void UTDRPGUWItemMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWItemMenu::Close);
	QuickSlotButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWItemMenu::RegisterQuickSlot);
}

void UTDRPGUWItemMenu::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UTDRPGUWItemMenu::Update(UItemBase* InItem)
{
	// FuncButton->OnClicked.Clear();
	SelectedItem = InItem;
}


void UTDRPGUWItemMenu::RegisterQuickSlot()
{

	if(IQuickSlotHandler* SlotHandler = Cast<IQuickSlotHandler>(SelectedItem))
	{
		// 퀵슬롯 받아오기
		UPlayerManager* PlayerManager = GetGameInstance()->GetSubsystem<UPlayerManager>();

		// 등록
		PlayerManager->QuickSlot->Register(SlotHandler);
	}
}