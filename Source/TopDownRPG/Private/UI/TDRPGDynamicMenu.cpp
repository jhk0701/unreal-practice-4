// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGDynamicMenu.h"
#include "UI/Element/TDRPGUWButton.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>


void UTDRPGDynamicMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->Button->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);

	for (int32 i = 0; i < DefaultButtonCount; ++i) 
	{
		UTDRPGUWButton* ButtonInst = CreateButton();

		ButtonInst->SetVisibility(ESlateVisibility::Hidden);

		ButtonPool.Enqueue(ButtonInst);
	}
}

void UTDRPGDynamicMenu::SetMenu(TArray<FString>& InLabel, TArray<TFunction<void>>& InFunction)
{
	check(InLabel.Num() == InFunction.Num());

	int32 Cnt = InLabel.Num();

	for (int32 i = 0; i < Cnt; ++i) 
	{
		UTDRPGUWButton* ButtonInst = GetButton();

		ButtonInst->Label->SetText(FText::FromString(InLabel[i]));
		
		// ButtonInst->Button->OnClicked.AddUnique()
	}
}

void UTDRPGDynamicMenu::Clear()
{
	while (!ActiveButtons.IsEmpty()) 
	{
		UTDRPGUWButton* ButtonInst;
		ActiveButtons.Dequeue(ButtonInst);

		ButtonInst->Button->OnClicked.Clear();
		ButtonInst->SetVisibility(ESlateVisibility::Hidden);

		ButtonPool.Enqueue(ButtonInst);
	}
}

UTDRPGUWButton* UTDRPGDynamicMenu::CreateButton()
{
	UTDRPGUWButton* Instance = CreateWidget<UTDRPGUWButton>(this, ButtonFactory);
	Container->AddChild(Instance);
	return Instance;
}

UTDRPGUWButton* UTDRPGDynamicMenu::GetButton()
{
	UTDRPGUWButton* ButtonInst;
	if (ButtonPool.IsEmpty())
		ButtonInst = CreateButton();
	else
		ButtonPool.Dequeue(ButtonInst);

	ButtonInst->SetVisibility(ESlateVisibility::Visible);

	ActiveButtons.Enqueue(ButtonInst);

	return ButtonInst;
}
