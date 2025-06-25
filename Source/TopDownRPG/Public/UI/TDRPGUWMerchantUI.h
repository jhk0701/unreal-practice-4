// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWMerchantUI.generated.h"

struct FMerchantDataRow;
enum class ETableType : uint8;

class UTDRPGUWProductSlot;
class UTDRPGUWInventorySlot;
class UTDRPGUWItemDetail;
class UTDRPGUWItemMenu;

class UButton;
class UTextBlock;
class UUniformGridPanel;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWMerchantUI : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> MerchantNameLabel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameLabel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> MerchantSideContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> PlayerSideContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UVerticalBox> Info;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWProductSlot> ProductSlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWInventorySlot> InventorySlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWItemDetail> DetailFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UTDRPGUWItemMenu> MenuFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UTDRPGUWItemDetail> Detail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UTDRPGUWItemMenu> Menu;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	int32 RowSize = 8;

public:
	virtual void NativeOnInitialized() override;
	
	void SetMerchant(FMerchantDataRow* InMerchantData);

protected:
	void InitProductSlot(FString& InProductID, ETableType InType, int32 InIndex);

	UTDRPGUWProductSlot* CreateProductSlot();


};
