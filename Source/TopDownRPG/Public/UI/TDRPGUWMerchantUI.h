// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWMerchantUI.generated.h"

struct FMerchantDataRow;
enum class ETableType : uint8;

class UButton;
class UTDRPGUWProductSlot;
class UTDRPGUWInventorySlot;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWMerchantUI : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> MerchantSideContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> PlayerSideContainer;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	TSubclassOf<UTDRPGUWProductSlot> ProductSlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	TSubclassOf<UTDRPGUWInventorySlot> InventorySlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement")
	int32 RowSize = 8;

	TQueue<UTDRPGUWProductSlot*> ActiveProductSlot;
	TQueue<UTDRPGUWProductSlot*> ProductSlotStorage;


public:
	virtual void NativeOnInitialized() override;
	
	void SetMerchant(FMerchantDataRow* InMerchantData);

protected:
	void InitProductSlot(FString& InProductID, ETableType InType, int32 InIndex);

	UTDRPGUWProductSlot* CreateProductSlot();
};
