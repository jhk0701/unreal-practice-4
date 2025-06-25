// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "TDRPGUWProductSlot.generated.h"

enum class ETableType : uint8;

UCLASS()
class TOPDOWNRPG_API UTDRPGUWProductSlot : public UTDRPGUWSlotBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString ProductID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ETableType ItemType;

public:
	virtual void Clear() override;

	virtual void Bind(FString& InProductID, ETableType InItemType);
	void GetProduct(FString& OutProductID, ETableType& OutItemType) const;

protected:
	virtual void InvokeButtonClick() override;

	void Refresh();
	void OnIconLoaded(UObject* Loaded);
	
};
