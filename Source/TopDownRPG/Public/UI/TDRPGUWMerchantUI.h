// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWMerchantUI.generated.h"

class ANPCMerchant;
enum class ETableType : uint8;

class UTDRPGUWSlotBase;
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

	TQueue<UTDRPGUWProductSlot*> ProductSlotPool;
	TQueue<UTDRPGUWProductSlot*> ActiveProductSlot;

	UPROPERTY()
	TObjectPtr<ANPCMerchant> Merchant;

public:
	virtual void NativeOnInitialized() override;
	virtual void Close() override;

	// void Init();
	void SetMerchant(ANPCMerchant* InMerchant);


protected:
	void InitProductSlot(const FString& InProductID, const ETableType InType, const int32 InIndex);

	UTDRPGUWProductSlot* CreateProductSlot();

	void Clear();

	void OnSlotClicked(UTDRPGUWSlotBase* InSlot);

	void OnClickBuy(const FString& InProductID, const ETableType InType);
	void OnClickSell();

};
