// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWLoadGameUI.h"
#include "Core/PlayerDataManager.h"
#include "UI/Element/TDRPGUWGameDataSlot.h"

#include <Components/ScrollBox.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>


void UTDRPGUWLoadGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitSlots();
	ShowScroll(0);
}

void UTDRPGUWLoadGameUI::InitSlots()
{
	if (!SlotFactory)  
		return;

	SlotInstances.Empty();

	for (int8 i = 0; i < SlotCount; ++i) 
	{
		UTDRPGUWGameDataSlot* SlotInst = CreateWidget<UTDRPGUWGameDataSlot>(this, SlotFactory);
		Scroll->AddChild(SlotInst);
		SlotInstances.Add(SlotInst);

		SlotInst->Index = i;
		SlotInst->OnSlotClicked.BindUObject(this, &UTDRPGUWLoadGameUI::OnSlotClicked);
		SlotInst->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTDRPGUWLoadGameUI::ShowScroll(int32 InIndex)
{
	ScrollIndex = InIndex;

	UPlayerDataManager* PlayerData = GetGameInstance()->GetSubsystem<UPlayerDataManager>();
	
	const TArray<FString>& Dir = PlayerData->GetPlayerData();
	for (int32 i = ScrollIndex; i < ScrollIndex + SlotCount; ++i)
	{
		int32 SlotIndex = i - ScrollIndex;

		if (i >= Dir.Num())
		{
			SlotInstances[SlotIndex]->SetVisibility(ESlateVisibility::Hidden);
			continue;
		}

		UTDRPGUWGameDataSlot* SlotInst = SlotInstances[SlotIndex];
		
		SlotInst->SlotName = Dir[i];

		SlotInst->NumLabel->SetText(FText::FromString(FString::Printf(TEXT("No. %d"), i + 1)));
		SlotInst->PlayerNameLabel->SetText(FText::FromString(Dir[i]));
		SlotInst->PlayerInfoLabel->SetText(FText());

		SlotInst->SetVisibility(ESlateVisibility::Visible);
	}
}

void UTDRPGUWLoadGameUI::OnSlotClicked(FString& InSlotName)
{
	FString str = InSlotName.Left(InSlotName.Len() - 4);

	// 불러오기 호출
	if (UPlayerDataManager* PlayerData = GetGameInstance()->GetSubsystem<UPlayerDataManager>())
		PlayerData->LoadData(str, FOnDataLoadCompleted::CreateUObject(this, &UTDRPGUWLoadGameUI::InvokeLoadCompleteCallback));
}

void UTDRPGUWLoadGameUI::InvokeLoadCompleteCallback()
{
	LoadCompleteCallback.ExecuteIfBound();
}
