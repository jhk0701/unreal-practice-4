// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWItemDetail.h"

#include "TDRPGEnum.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"
#include "Core/ResourceLoadManager.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>


void UTDRPGUWItemDetail::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	QuantityTitle->SetVisibility(bShowQuantity ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	QuantityLabel->SetVisibility(bShowQuantity ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	RarityTitle->SetVisibility(bShowRarity ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	RarityLabel->SetVisibility(bShowRarity ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UTDRPGUWItemDetail::Update(UItemBase* InItem)
{
	if (!InItem)
		return;

	Update(InItem->GetData());

	QuantityLabel->SetText(FText::FromString(FString::Printf(TEXT("%u"), InItem->Quantity)));
}

void UTDRPGUWItemDetail::Update(FItemDataRow* InData)
{
	FItemDataRow* Data = InData;

	NameLabel->SetText(FText::FromName(Data->ItemName));
	RarityLabel->SetText(FText::FromString(FTDRPGEnum::EnumToString(Data->Rarity)));
	PriceLabel->SetText(FText::FromString(FString::Printf(TEXT("%u G"), Data->Price)));

	if (Data->Thumbnail.IsValid())
	{
		UTexture2D* Tex = Cast<UTexture2D>(Data->Thumbnail.ResolveObject());
		IconImage->SetBrushFromTexture(Tex);
	}
	else
	{
		UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
		Resource->Load(Data->Thumbnail,
			FOnResourceLoaded::CreateLambda(
				[this](UObject* Loaded)
				{
					if (UTexture2D* Tex = Cast<UTexture2D>(Loaded))
					{
						this->IconImage->SetBrushFromTexture(Tex);
					}
				})
		);
	}
}

void UTDRPGUWItemDetail::UpdatePrice(uint32 InPrice)
{
	PriceLabel->SetText(FText::FromString(FString::Printf(TEXT("%u G"), InPrice)));
}
