// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIMerchantUI.generated.h"

struct FMerchantDataRow;
enum class ETableType : uint8;

class UUIProductSlot;
class UUIInventorySlot;
class UUIItemDetail;
class UUIItemMenu;

class UButton;
class UTextBlock;
class UUniformGridPanel;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIMerchantUI : public UUIBase
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
	TSubclassOf<UUIProductSlot> ProductSlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UUIInventorySlot> InventorySlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UUIItemDetail> DetailFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement|Factory")
	TSubclassOf<UUIItemMenu> MenuFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UUIItemDetail> Detail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement|Sub")
	TObjectPtr<UUIItemMenu> Menu;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	int32 RowSize = 8;

public:
	virtual void NativeOnInitialized() override;
	
	void SetMerchant(FMerchantDataRow* InMerchantData);

protected:
	void InitProductSlot(FString& InProductID, ETableType InType, int32 InIndex);

	UUIProductSlot* CreateProductSlot();


};
