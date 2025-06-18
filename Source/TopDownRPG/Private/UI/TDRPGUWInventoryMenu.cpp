// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWInventoryMenu.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>

#include "Item/ConsumeItem.h"
#include "Item/EquipmentItem.h"

#include "Core/TDRPGGameState.h"
#include "Character/TDRPGPlayer.h"

#include "Core/PlayerManager.h"
#include "Player/QuickSlot.h"


void UTDRPGUWInventoryMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	QuickSlotButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWInventoryMenu::RegisterQuickSlot);
}

void UTDRPGUWInventoryMenu::Update(UItemBase* InItem)
{
	Super::Update(InItem);

	if (!InItem) 
		return;

	if (SelectedItem->IsA<UEquipmentItem>())
	{
		FuncLabel->SetText(FText::FromString(TEXT("Equip")));
	}
	else if (UConsumeItem* Consumable = Cast<UConsumeItem>(SelectedItem))
	{
		FuncLabel->SetText(FText::FromString(TEXT("Use")));

		// 퀵슬롯 설정
		FText QuickLabel = FText::FromString(Consumable->IsRegistered() ? TEXT("Unregister") : TEXT("Register"));
		QuickSlotLabel->SetText(QuickLabel);
		QuickSlotButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UTDRPGUWInventoryMenu::InvokeFunc()
{
	if (UConsumeItem* Consumable = Cast<UConsumeItem>(SelectedItem))
	{
		ATDRPGGameState* GameState = Cast<ATDRPGGameState>(GetWorld()->GetGameState());
		Consumable->Use(GameState->Player.Get());
	}
	else if (UEquipmentItem* Equipment = Cast<UEquipmentItem>(SelectedItem))
	{
		UPlayerManager* PlayerManager = GetGameInstance()->GetSubsystem<UPlayerManager>();
		Equipment->Equip(PlayerManager);
	}

	Super::InvokeFunc();
}

void UTDRPGUWInventoryMenu::RegisterQuickSlot()
{
	// 퀵슬롯 받아오기
	UPlayerManager* PlayerManager = GetGameInstance()->GetSubsystem<UPlayerManager>();

	if (IQuickSlotHandler* SlotHandler = Cast<IQuickSlotHandler>(SelectedItem))
	{
		if (SlotHandler->IsRegistered())
		{
			PlayerManager->QuickSlot->Unregister(SlotHandler->GetSlotIndex()); // 등록 해제
		}
		else
		{
			uint8 Index = 0; // 등록

			if (PlayerManager->QuickSlot->Register(SlotHandler, Index))
				SlotHandler->RegisterSlot(Index);
		}
	}

	Close();
}
