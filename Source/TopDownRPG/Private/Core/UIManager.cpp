// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UIManager.h"

#include "UI/UIConfig.h"
#include "UI/TDRPGUserWidget.h"

#include <Components/CanvasPanelSlot.h>

void UUIManager::SetHUD(ATDRPGHUD* InHUD)
{
	CurrentHUD = InHUD;
}

void UUIManager::InitUIConfig(UUIConfig* InConfig)
{
	if (!InConfig) 
		return;

	for (auto& Element : InConfig->Elements) 
	{
		UTDRPGUserWidget* Widget = CreateWidget<UTDRPGUserWidget>(GetWorld(), Element.WidgetClass);
		
		if (!Widget) 
			continue;
			
		UIMap.Add(Element.ElementID, Widget);

		Widget->AddToViewport();

		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget))
		{
			CanvasPanelSlot->SetPosition(Element.Position);
		}
	}
}

UTDRPGUserWidget* UUIManager::GetUI(const FString& InID)
{
	if (UIMap.Contains(InID))
		return UIMap[InID];

	return nullptr;
}
