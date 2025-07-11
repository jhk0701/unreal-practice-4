// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Element/TDRPGUWSkillListSlot.h"

#include "TDRPGEnum.h"
#include "Core/ResourceLoadManager.h"
#include "Data/SkillDataRow.h"
#include "Character/Skill/Skill.h"

#include "UI/DragDropWidget.h"
#include "UI/Element/TDRPGUWSkillSlot.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Blueprint/SlateBlueprintLibrary.h>

#include "TopDownRPG/TopDownRPG.h"

void UTDRPGUWSkillListSlot::Refresh()
{
	USkill* Skill = Cast<USkill>(Model);
	check(Skill);

	FSkillDataRow& Data = Skill->GetData();

	NameLabel->SetText(FText::FromName(Data.Name));

	FString InputType = FTDRPGEnum::EnumToString(Data.InputType);
	InputLabel->SetText(FText::FromString(FString::Printf(TEXT("[%s]"), *InputType)));

	FString CostStr = "";
	for(auto& Pair : Data.Requirement)
	{
		CostStr.Append(FTDRPGEnum::EnumToString(Pair.Key));
		CostStr.Append(FString::Printf(TEXT(" Cost %d"), Pair.Value));
	}

	CostLabel->SetText(FText::FromString(CostStr));
	CooldownLabel->SetText(FText::FromString(FString::Printf(TEXT("Cooldown %d sec"), Data.Cooldown)));

	UResourceLoadManager* Resource = GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	Resource->Load(Data.Thumbnail, FOnResourceLoaded::CreateLambda(
		[this](UObject* Loaded)
		{
			if (UTexture2D* LoadedTex = Cast<UTexture2D>(Loaded))
			{
				IconImage->SetBrushFromTexture(LoadedTex, true);
				IconImage->SetOpacity(1.0f);
				IconImage->SetVisibility(ESlateVisibility::Visible);
			}
		}
	));
}

FReply UTDRPGUWSkillListSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Result.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	return Result;
}

void UTDRPGUWSkillListSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropWidget* DragDropOp = NewObject<UDragDropWidget>();
	// 드래그 중인 위젯
	DragDropOp->WidgetReference = this;
	// 넘길 정보
	DragDropOp->Payload = Model;
	// 드래그 중 표시중인 위젯
	UTDRPGUWSlotBase* DragVisualInst = CreateWidget<UTDRPGUWSlotBase>(GetWorld(), DragVisual);
	UImage* ImageWidget = DragVisualInst->GetIconWidget();
	ImageWidget->SetBrush(IconImage->GetBrush());
	ImageWidget->SetOpacity(0.7f);
	ImageWidget->SetVisibility(ESlateVisibility::Visible);
	DragDropOp->DefaultDragVisual = DragVisualInst;

	OutOperation = DragDropOp;
}

void UTDRPGUWSkillListSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	PRINT_LOG(TEXT("NativeOnDragCancelled"));
}
