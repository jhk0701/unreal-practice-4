// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UIManager.h"

#include "UI/UIConfig.h"
#include "UI/TDRPGUserWidget.h"

#include <Components/CanvasPanelSlot.h>


void UUIManager::InitUIConfig(UUIConfig* InConfig)
{
	if (!InConfig) 
		return;

	for (auto& Element : InConfig->Elements) 
	{
		UTDRPGUserWidget* Widget = CreateWidget<UTDRPGUserWidget>(GetWorld(), Element.WidgetClass);
		
		if (!Widget) 
			continue;

		FString Key = Element.WidgetClass.Get()->GetFName().ToString();
		UIMap.Add(Key, Widget);

		Widget->AddToViewport();
		
		if (!Element.bCanOpenOnInit)
			Widget->SetVisibility(ESlateVisibility::Hidden);

		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget))
		{
			CanvasPanelSlot->SetPosition(Element.Position);
		}
	}
}