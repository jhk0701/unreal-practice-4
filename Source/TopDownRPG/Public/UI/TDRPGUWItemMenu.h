// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWItemMenu.generated.h"

class UTextBlock;
class UButton;
class UItemBase;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWItemMenu : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	// 사용하기, 장착하기
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> FuncButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> FuncLabel;

	// 닫기
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	// 퀵슬롯 등록 및 해제 -> 드래그앤 드롭 가능하게
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> QuickSlotButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuickSlotLabel;

public:
	virtual void NativeOnInitialized() override;

	virtual void Close() override;

	void Update(UItemBase* InItem);

	void RegisterQuickSlot();
};
