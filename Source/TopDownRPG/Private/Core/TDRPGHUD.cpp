// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TDRPGHUD.h"
#include "Core/UIManager.h"

#include "TDRPGEnum.h"
#include "UI/UIConfig.h"
#include "UI/DragDropWidget.h"
#include "UI/TDRPGUWCanvas.h"

#include <Components/CanvasPanelSlot.h>

#include "TopDownRPG/TopDownRPG.h"

ATDRPGHUD::ATDRPGHUD()
{
	ConstructorHelpers::FClassFinder<UTDRPGUWCanvas> DefaultCanvas(TEXT("WidgetBlueprint'/Game/4-UI/WBP_TDRPGUWCanvas.WBP_TDRPGUWCanvas_C'"));

	if (DefaultCanvas.Succeeded())
		CanvasFactory = DefaultCanvas.Class;
}

void ATDRPGHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitHUD();
}

void ATDRPGHUD::InitHUD()
{
	UGameInstance* GameInst = GetGameInstance();
	if (!GameInst)
		return;

	InitCanvas();

	UUIManager* UIManager = GameInst->GetSubsystem<UUIManager>();
	UIManager->SetHUD(this);
	
	for (auto Config : Configs) 
		InitUIConfig(Config);
}

void ATDRPGHUD::InitCanvas()
{
	uint8 Cnt = (uint8)EUILayer::COUNT;

	for (uint8 i = 0; i < Cnt; ++i)
	{
		EUILayer Type = (EUILayer)i;

		if (!Layer.Contains(Type))
			Layer.Add(Type, CreateCanvas());
		else if (Layer[Type] == nullptr)
			Layer[Type] = CreateCanvas();
		else
			Layer[Type]->AddToViewport();
	}
}

UTDRPGUWCanvas* ATDRPGHUD::CreateCanvas()
{
	check(CanvasFactory);

	UTDRPGUWCanvas* CanvasInst = CreateWidget<UTDRPGUWCanvas>(GetWorld(), CanvasFactory);
	CanvasInst->AddToViewport();

	return CanvasInst;
}

void ATDRPGHUD::InitUIConfig(UUIConfig* InConfig)
{
	if (!InConfig)
		return;

	for (FUIElementData& Element : InConfig->Elements)
	{
		FString Key = Element.WidgetClass.Get()->GetFName().ToString();

		if (UIMap.Contains(Key) && UIMap[Key])
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

