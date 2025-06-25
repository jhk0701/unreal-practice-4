// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UINewGameUI.generated.h"

class UButton;
class UWidgetSwitcher;
class UUIClassSelection;
class UUIInputPlayerName;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUINewGameUI : public UUIBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> BodySwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUIClassSelection> ClassSelectionPage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUIInputPlayerName> InputPlayerNamePage;

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
