// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWTitle.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS(BlueprintType)
class TOPDOWNRPG_API UTDRPGUWTitle : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleLabel;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

protected:
	virtual void NativeOnInitialized() override;
	void InitButton();
};
