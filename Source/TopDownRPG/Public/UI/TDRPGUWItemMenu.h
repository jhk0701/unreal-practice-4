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

protected:
	UItemBase* SelectedItem;

public:
	virtual void NativeOnInitialized() override;

	virtual void Update(UItemBase* InItem);

	UFUNCTION()
	virtual void InvokeFunc();
};
