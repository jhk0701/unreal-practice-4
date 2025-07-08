// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWInventorySlot.h"

#include "Core/ResourceLoadManager.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWInventorySlot::Clear()
{
	if (Model)
	{
		GetItem()->OnItemUpdated.RemoveAll(this);
		Model = nullptr;
	}

	QuantityLabel->SetVisibility(ESlateVisibility::Hidden);

	Super::Clear();
}


void UTDRPGUWInventorySlot::Bind(UDataModel* InModel)
{
	if (!InModel)
		return;

	if (Model)
		GetItem()->OnItemUpdated.RemoveAll(this);

	Model = InModel;
	GetItem()->OnItemUpdated.AddUObject(this, &UTDRPGUWInventorySlot::Refresh);

	Refresh(Model);
}

void UTDRPGUWInventorySlot::Bind(UItemBase* InItem)
{
	if (UDataModel* InModel = Cast<UDataModel>(InItem))
		Bind(InModel);
}

void UTDRPGUWInventorySlot::Unbind()
{
	Clear();
}

void UTDRPGUWInventorySlot::Refresh(UDataModel* InModel)
{
	if (!InModel)
		return;

	UItemBase* Item = Cast<UItemBase>(InModel);
	FItemDataRow* Data = Item->GetData();

	QuantityLabel->SetVisibility(ESlateVisibility::Visible);
	QuantityLabel->SetText(FText::FromString(FString::Printf(TEXT("%u"), Item->Quantity)));

	UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	Resource->Load(Data->Thumbnail, FOnResourceLoaded::CreateUObject(this, &UTDRPGUWInventorySlot::OnIconLoaded));
}

UItemBase* UTDRPGUWInventorySlot::GetItem() const
{
	return Cast<UItemBase>(Model);
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
	if (Model)
		Super::InvokeCursorEnter();
}

void UTDRPGUWInventorySlot::InvokeCursorLeave()
{
	if (Model)
		Super::InvokeCursorLeave();
}

void UTDRPGUWInventorySlot::InvokeButtonClick()
{
	if (Model)
		OnButtonClicked.Broadcast(this);
}
