// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/UIInventorySlot.h"

#include "Core/ResourceLoadManager.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "TopDownRPG/TopDownRPG.h"



void UUIInventorySlot::Bind(UItemBase* InItem)
{
	if (!InItem)
		return;

	if (Item)
		Item->OnItemUpdated.RemoveAll(this);

	Item = InItem;
	Item->OnItemUpdated.AddUObject(this, &UUIInventorySlot::Refresh);

	Refresh(Item);
}

void UUIInventorySlot::Clear()
{
	if (Item)
	{
		Item->OnItemUpdated.RemoveAll(this);
		Item = nullptr;
	}

	Super::Clear();
}

void UUIInventorySlot::Refresh(UItemBase* InItem)
{
	if (!InItem)
		return;

	FItemDataRow* Data = InItem->GetData();

	if (QuantityLabel)
	{
		QuantityLabel->SetVisibility(ESlateVisibility::Visible);
		QuantityLabel->SetText(FText::FromString(FString::Printf(TEXT("%u"), InItem->Quantity)));
	}

	UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	Resource->Load(Data->Thumbnail, FOnResourceLoaded::CreateUObject(this, &UUIInventorySlot::OnIconLoaded));
}


void UUIInventorySlot::OnIconLoaded(UObject* Loaded)
{
	if (!Loaded)
		return;

	if (UTexture2D* Tex = Cast<UTexture2D>(Loaded))
	{
		IconImage->SetBrushFromTexture(Tex, true);
		IconImage->SetOpacity(1.0f);
		IconImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUIInventorySlot::InvokeCursorEnter()
{
	if (Item)
		Super::InvokeCursorEnter();
}

void UUIInventorySlot::InvokeCursorLeave()
{
	if (Item)
		Super::InvokeCursorLeave();
}

void UUIInventorySlot::InvokeButtonClick()
{
	if (Item)
		OnButtonClicked.Broadcast(this);
}
