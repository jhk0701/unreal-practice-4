// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWStageResult.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWStageResult : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ReturnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NextButton;

public:
	void SetResult(bool bIsCleared);

protected:
	virtual void NativeOnInitialized() override;
	void BindButton();

};
