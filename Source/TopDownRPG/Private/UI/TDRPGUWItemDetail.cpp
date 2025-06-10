// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWItemDetail.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"
#include "Core/ResourceLoadManager.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>


void UTDRPGUWItemDetail::Update(UItemBase* InItem)
{
	if (!InItem)
		return;

	FItemDataRow* Data = InItem->GetData();
	
	NameLabel->SetText(FText::FromName(Data->ItemName));
	QuantityLabel->SetText(FText::FromString(FString::Printf(TEXT("%u"), InItem->GetQuantity())));
	RarityLabel->SetText(FText::FromString(InItem->EnumToString(Data->Rarity)));

	if (Data->Thumbnail.IsValid())
	{
		UTexture2D* Tex = Cast<UTexture2D>(Data->Thumbnail.ResolveObject());
		IconImage->SetBrushFromTexture(Tex);
	}
	else
	{
		UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
		FOnResourceLoaded Delegate = FOnResourceLoaded::CreateLambda([this](UObject* Loaded) 
			{
				if(UTexture2D* Tex = Cast<UTexture2D>(Loaded))
				{
					this->IconImage->SetBrushFromTexture(Tex);
				}
			});
		Resource->Load(Data->Thumbnail, Delegate);
	}
}
