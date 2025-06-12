// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSlotBase.h"

#include "Core/ResourceLoadManager.h"
#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Components/Button.h>

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWSlotBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SlotButton)
		SlotButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUWSlotBase::InvokeButtonClick);

	Clear();
}

void UTDRPGUWSlotBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (Item)
		OnCursorEnter.Broadcast(Item);
}

void UTDRPGUWSlotBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (Item)
		OnCursorLeave.Broadcast();
}

void UTDRPGUWSlotBase::Clear()
{
	// Optional이라 방어코드 추가
	if (QuantityLabel)
		QuantityLabel->SetVisibility(ESlateVisibility::Hidden);

	IconImage->SetVisibility(ESlateVisibility::Hidden);
	IconImage->SetBrushResourceObject(nullptr);
}

void UTDRPGUWSlotBase::SetData(UItemBase* InItem)
{
	if (!InItem)
		return;

	if (Item)
	{
		// 델리게이트에 등록된 특정 오브젝트 메소드들을 제거
		Item->OnItemUpdated.RemoveAll(this);
	}
		
	Item = InItem;
	Item->OnItemUpdated.AddUObject(this, &UTDRPGUWSlotBase::Refresh);

	Refresh(Item);
}

void UTDRPGUWSlotBase::Refresh(UItemBase* InItem)
{
	if (!InItem)
		return;

	PRINT_LOG(TEXT("Refresh"));

	FItemDataRow* Data = InItem->GetData();

	QuantityLabel->SetVisibility(ESlateVisibility::Visible);
	QuantityLabel->SetText(FText::FromString(FString::Printf(TEXT("%u"), InItem->GetQuantity())));

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

void UTDRPGUWSlotBase::InvokeButtonClick()
{
	if (Item)
		OnButtonClicked.Broadcast(Item);
}
