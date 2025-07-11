// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSkillSlot.h"
#include "TDRPGUWSkillListSlot.generated.h"

class UTDRPGUWSlotBase;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSkillListSlot : public UTDRPGUWSkillSlot
{
	GENERATED_BODY()

public:
	virtual void Refresh() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drag And Drop")
	TSubclassOf<UTDRPGUWSlotBase> DragVisual;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InputLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CostLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownLabel;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	/*
	UMG_API virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	UMG_API virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	UMG_API virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	UMG_API virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	UMG_API virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	UMG_API virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	*/
};
