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
UCLASS()
class TOPDOWNRPG_API UTDRPGUWTitle : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleLabel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

public:
	virtual void NativeOnInitialized() override;

};
