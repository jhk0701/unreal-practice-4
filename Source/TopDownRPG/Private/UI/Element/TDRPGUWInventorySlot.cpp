// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWInventorySlot.h"

#include "Core/ResourceLoadManager.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWInventorySlot::Bind(UItemBase* InItem)
{
	if (!InItem)
		return;

	if (Item)
		Item->OnItemUpdated.RemoveAll(this);

	Item = InItem;
	Item->OnItemUpdated.AddUObject(this, &UTDRPGUWInventorySlot::Refresh);

	Refresh(Item);
}

void UTDRPGUWInventorySlot::Clear()
{
	if (Item)
	{
		Item->OnItemUpdated.RemoveAll(this);
		Item = nullptr;
	}

	Super::Clear();
}

void UTDRPGUWInventorySlot::Refresh(UItemBase* InItem)
{
	if (!InItem)
		return;

	FItemDataRow* Data = InItem->GetData();

	QuantityLabel->SetVisibility(ESlateVisibility::Visible);
	QuantityLabel->SetText(FText::FromString(FString::Printf(TEXT("%u"), InItem->Quantity)));

	UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	Resource->Load(Data->Thumbnail, FOnResourceLoaded::CreateUObject(this, &UTDRPGUWInventorySlot::OnIconLoaded));
}


void UTDRPGUWInventorySlot::OnIconLoaded(UObject* Loaded)
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

void UTDRPGUWInventorySlot::InvokeCursorEnter()
{
	if (Item)
		Super::InvokeCursorEnter();
}

void UTDRPGUWInventorySlot::InvokeCursorLeave()
{
	if (Item)
		Super::InvokeCursorLeave();
}

void UTDRPGUWInventorySlot::InvokeButtonClick()
{
	if (Item)
		OnButtonClicked.Broadcast(this);
}
