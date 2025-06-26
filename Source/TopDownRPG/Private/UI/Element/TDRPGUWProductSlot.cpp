// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWProductSlot.h"
#include "CommonConst.h"

#include "Core/ResourceLoadManager.h"
#include "Core/GameDataManager.h"
#include "Data/ItemDataRow.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>


void UTDRPGUWProductSlot::Clear()
{
	ProductID = CommonConst::EMPTY_ITEM_ID;

	Super::Clear();
}

void UTDRPGUWProductSlot::Bind(const FString& InProductID, const ETableType InItemType)
{
	ProductID = InProductID;
	ItemType = InItemType;
	
	Refresh();
}

void UTDRPGUWProductSlot::GetProduct(FString& OutProductID, ETableType& OutItemType) const
{
	OutProductID = ProductID;
	OutItemType = ItemType;
}

void UTDRPGUWProductSlot::InvokeButtonClick()
{
	if (ProductID == CommonConst::EMPTY_ITEM_ID)
		return;

	OnButtonClicked.Broadcast(this);
}

void UTDRPGUWProductSlot::Refresh()
{
	if (ProductID == CommonConst::EMPTY_ITEM_ID)
		return;

	UGameDataManager* GameDate = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FItemDataRow* Data = GameDate->GetRow<FItemDataRow>(ItemType, ProductID);

	if (!Data)
		return;

	UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	Resource->Load(Data->Thumbnail, FOnResourceLoaded::CreateUObject(this, &UTDRPGUWProductSlot::OnIconLoaded));
}

void UTDRPGUWProductSlot::OnIconLoaded(UObject* Loaded)
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
