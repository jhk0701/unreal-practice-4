// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NPC/TDRPGNPCBase.h"
#include "NPCMerchant.generated.h"

struct FMerchantDataRow;
enum class ETableType : uint8;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ANPCMerchant : public ATDRPGNPCBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCData")
	FString MerchantID;

public:
	ANPCMerchant();

	virtual void Interact() override;

	FMerchantDataRow* GetData();

	// 상인에게서 아이템 구매
	void BuyItem(const FString& InProductID, const ETableType& InType, const uint8& InQuantity = 1);
	
};
