// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Element/TDRPGUWSlotBase.h"
#include "Inherit/Bindable.h"
#include "TDRPGUWProductSlot.generated.h"

enum class ETableType : uint8;

/// <summary>
/// 인벤토리 슬롯과 달리 ID만으로 사용할 용도
/// </summary>
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

	virtual void Bind(const FString& InProductID, const ETableType InItemType);
	void GetProduct(FString& OutProductID, ETableType& OutItemType) const;
	void Refresh();

protected:
	virtual void InvokeButtonClick() override;
	void OnIconLoaded(UObject* Loaded);
	
};
