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

	// virtual void Bind() = 0;
	// virtual void Unbind() = 0;
};
