// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGDynamicMenu.generated.h"

class UTDRPGUWButton;
class UPanelWidget;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGDynamicMenu : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWButton> ButtonFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UPanelWidget> Container;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTDRPGUWButton> CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	int32 DefaultButtonCount = 5;

	TQueue<UTDRPGUWButton*> ActiveButtons;
	TQueue<UTDRPGUWButton*> ButtonPool;

public:
	void SetMenu(TArray<FString>& InLabel, TArray<TFunction<void>>& InFunction);

protected:
	virtual void NativeOnInitialized() override;

	void Clear();

	UTDRPGUWButton* CreateButton();
	UTDRPGUWButton* GetButton();

};
