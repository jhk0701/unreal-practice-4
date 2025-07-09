// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UIManager.h"

#include "TDRPGEnum.h"
#include "UI/UIConfig.h"
#include "UI/TDRPGUserWidget.h"
#include "UI/TDRPGUWCanvas.h"

#include <Components/CanvasPanelSlot.h>

#include "TopDownRPG/TopDownRPG.h"


UUIManager::UUIManager()
{
	ConstructorHelpers::FClassFinder<UTDRPGUWCanvas> DefaultCanvas(TEXT("WidgetBlueprint'/Game/4-UI/WBP_TDRPGUWCanvas.WBP_TDRPGUWCanvas_C'"));
	
	if (DefaultCanvas.Succeeded())
		CanvasFactory = DefaultCanvas.Class;
}

void UUIManager::InitCanvas()
{
	Layer.Empty();

	check(CanvasFactory);

	uint8 Cnt = (uint8)EUILayer::COUNT;
	for(uint8 i = 0; i < Cnt; ++i)
	{
		UTDRPGUWCanvas* Canvas = CreateWidget<UTDRPGUWCanvas>(GetWorld(), CanvasFactory);
		Canvas->AddToViewport();
		Layer.Add((EUILayer)i, Canvas);
	}
}

void UUIManager::InitUIConfig(UUIConfig* InConfig)
{
	if (!InConfig) 
		return;

	for (auto& Element : InConfig->Elements) 
	{
		FString Key = Element.WidgetClass.Get()->GetFName().ToString();
		
		if (UIMap.Contains(Key))
			return;

		UTDRPGUserWidget* Widget = CreateWidget<UTDRPGUserWidget>(GetWorld(), Element.WidgetClass);
		
		if (!Widget) 
			continue;

		UIMap.Add(Key, Widget);

		Layer[Element.Order]->AddToCanvas(Widget);

		Widget->InitWidget();
		Widget->SetVisibility(Element.bCanOpenOnInit ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Slot);
		check(CanvasPanelSlot);

		if (Element.bFillScreen)
		{
			CanvasPanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
			CanvasPanelSlot->SetOffsets(FMargin(0));
		}
		else
		{
			CanvasPanelSlot->SetPosition(Element.Position);
			CanvasPanelSlot->SetSize(Element.Size);
		}
	}
}