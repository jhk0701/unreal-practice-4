// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonConst.h"
#include "Templates/EnableIf.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemFactory.generated.h"

class UItemBase;
enum class ETableType :uint8;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UItemFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	template<typename T>
	inline TEnableIf<TIsDerivedFrom<T, UItemBase>::Value, T*>::Type
	GetItem(const FString& InItemID, uint32 InQuantity = 1)
	{
		if (InItemID == CommonConst::EMPTY_ITEM_ID)
			return nullptr;

		T* Item = NewObject<T>();
		Item->Initialize(InItemID, GetGameInstance(), InQuantity);

		return Item;
	};

	UItemBase* GetItem(ETableType ItemType, const FString& InItemID, uint32 InQuantity = 1);
};
