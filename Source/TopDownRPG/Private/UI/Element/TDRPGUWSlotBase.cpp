// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSlotBase.h"

#include "Core/ResourceLoadManager.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWSlotBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Clear();
}

void UTDRPGUWSlotBase::Clear()
{
	QuantityLabel->SetVisibility(ESlateVisibility::Hidden);
	IconImage->SetVisibility(ESlateVisibility::Hidden);
	IconImage->SetBrushResourceObject(nullptr);
}

void UTDRPGUWSlotBase::SetData(UItemBase* InItem)
{
	Item = InItem;

	if (!Item)
		return;

	Refresh();
}

void UTDRPGUWSlotBase::Refresh()
{
	FItemDataRow* Data = Item->GetData();

	QuantityLabel->SetVisibility(ESlateVisibility::Visible);
	QuantityLabel->SetText(FText::FromString(FString::Printf(TEXT("%u"), Item->GetQuantity())));

	UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	FOnResourceLoaded Delegate = FOnResourceLoaded::CreateUObject(this, &UTDRPGUWSlotBase::OnIconLoaded);
	Resource->Load(Data->Thumbnail, Delegate);
}

void UTDRPGUWSlotBase::OnIconLoaded(UObject* Loaded)
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
