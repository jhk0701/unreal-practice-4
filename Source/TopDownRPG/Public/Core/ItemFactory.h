// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Templates/EnableIf.h"
#include "ItemFactory.generated.h"

class UItemBase;
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
	GetItem(const FString& InItemID, const uint32 InQuantity = 1)
	{
		T* Item = NewObject<T>();
		Item->Initialize(InItemID, GetGameInstance(), InQuantity);
	};

};
