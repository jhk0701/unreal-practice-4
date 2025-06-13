// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWItemMenu.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>

#include "Character/TDRPGPlayer.h"

#include "Core/TDRPGGameState.h"
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
	FuncButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWItemMenu::InvokeFunc);
}


void UTDRPGUWItemMenu::Update(UItemBase* InItem)
{
	if (!InItem) return;

	SelectedItem = InItem;

	if (SelectedItem->IsA<UConsumeItem>())
		FuncLabel->SetText(FText::FromString(TEXT("Use")));
	else if (SelectedItem->IsA<UEquipmentItem>())
		FuncLabel->SetText(FText::FromString(TEXT("Equip")));
}

void UTDRPGUWItemMenu::InvokeFunc()
{
	if (UConsumeItem* Consumable = Cast<UConsumeItem>(SelectedItem))
	{
		ATDRPGGameState* GameState = Cast<ATDRPGGameState>(GetWorld()->GetGameState());
		
		Consumable->Use(GameState->Player.Get());
	}
	else if (UEquipmentItem* Equipment = Cast<UEquipmentItem>(SelectedItem)) 
	{
		Equipment->Equip();
	}
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