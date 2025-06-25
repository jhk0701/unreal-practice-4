// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UILoadGameUI.h"
#include "Core/PlayerDataManager.h"
#include "UI/Element/UIGameDataSlot.h"

#include <Components/ScrollBox.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>

#include "TopDownRPG/TopDownRPG.h"


void UUILoadGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Scroll->OnUserScrolled.AddUniqueDynamic(this, &UUILoadGameUI::OnScrollChanged);
	CloseButton->OnClicked.AddUniqueDynamic(this, &UUIBase::Close);

	InitSlots();
	ShowScroll(0);
}

void UUILoadGameUI::InitSlots()
{
	if (!SlotFactory)  
		return;

	SlotInstances.Empty();

	for (int8 i = 0; i < SlotCount; ++i) 
	{
		UUIGameDataSlot* SlotInst = CreateWidget<UUIGameDataSlot>(this, SlotFactory);
		Scroll->AddChild(SlotInst);
		SlotInstances.Add(SlotInst);

		SlotInst->Index = i;
		SlotInst->OnSlotClicked.BindUObject(this, &UUILoadGameUI::OnSlotClicked);
		SlotInst->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUILoadGameUI::ShowScroll(int32 InIndex)
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

		UUIGameDataSlot* SlotInst = SlotInstances[SlotIndex];
		
		SlotInst->SlotName = Dir[i];

		SlotInst->NumLabel->SetText(FText::FromString(FString::Printf(TEXT("No. %d"), i + 1)));
		SlotInst->PlayerNameLabel->SetText(FText::FromString(Dir[i]));
		SlotInst->PlayerInfoLabel->SetText(FText());

		SlotInst->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUILoadGameUI::OnScrollChanged(float InOffset)
{
	OffsetDelta = InOffset - CurrentOffset;
	CurrentOffset = InOffset;

	if (FMath::IsNearlyZero(CurrentOffset) && FMath::IsNearlyZero(OffsetDelta))
	{
		// Page Up
		// PRINT_LOG(TEXT("Page Up"));
		
		ShowScroll(FMath::Max(ScrollIndex - SlotCount, 0));
	}
	else if (FMath::IsNearlyEqual(CurrentOffset, Scroll->GetScrollOffsetOfEnd()) && FMath::IsNearlyZero(OffsetDelta))
	{
		// Page Down
		// PRINT_LOG(TEXT("Page Down"));

		UPlayerDataManager* PlayerData = GetGameInstance()->GetSubsystem<UPlayerDataManager>();
		int32 DataCnt = PlayerData->GetPlayerData().Num();

		int32 NewIndex = ScrollIndex + SlotCount;
		NewIndex >= DataCnt ? NewIndex = DataCnt - SlotCount - 1 : NewIndex;

		ShowScroll(NewIndex);

		Scroll->SetScrollOffset(10);
	}
}

void UUILoadGameUI::OnSlotClicked(FString& InSlotName)
{
	FString str = InSlotName.Left(InSlotName.Len() - 4);

	// 불러오기 호출
	if (UPlayerDataManager* PlayerData = GetGameInstance()->GetSubsystem<UPlayerDataManager>())
		PlayerData->LoadData(str, FOnDataLoadCompleted::CreateUObject(this, &UUILoadGameUI::InvokeLoadCompleteCallback));
}

void UUILoadGameUI::InvokeLoadCompleteCallback()
{
	LoadCompleteCallback.ExecuteIfBound();
}
