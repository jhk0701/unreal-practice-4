// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickSlotHandler.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuickSlotHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNRPG_API IQuickSlotHandler
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InvokeSlot(AActor* Subject) = 0;
	virtual uint8 GetIndex() = 0;

	inline virtual void RegisterSlot(uint8 InIndex) 
	{
		bIsInQuickSlot = true;
		QuickSlotIndex = InIndex;
	}
	inline virtual void UnregisterSlot() { bIsInQuickSlot = false; }
	
	inline virtual bool IsRegistered() const { return bIsInQuickSlot; }
	
	inline virtual uint8 GetSlotIndex() const { return QuickSlotIndex; }
	

protected:
	bool bIsInQuickSlot = false;
	uint8 QuickSlotIndex = 0;
};
