// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWNewGameUI.generated.h"

class UButton;
class UWidgetSwitcher;
class UTDRPGUWClassSelection;
class UTDRPGUWInputPlayerName;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWNewGameUI : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> BodySwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTDRPGUWClassSelection> ClassSelectionPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTDRPGUWInputPlayerName> InputPlayerNamePage;

public:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OpenClassSelectPage();

	UFUNCTION()
	void OpenInputNamePage();

	UFUNCTION()
	void Complete();

};
