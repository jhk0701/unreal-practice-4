// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIStageResult.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIStageResult : public UUIBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultLabel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UButton> ReturnButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UButton> NextButton;

public:
	void SetResult(bool bIsCleared);

protected:
	virtual void NativeOnInitialized() override;
	void BindButton();

};
