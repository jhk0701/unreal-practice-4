// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Bindable.generated.h"

class UDataModel;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBindable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNRPG_API IBindable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UDataModel* Model;

public:
	virtual void Bind(UDataModel* InModel) = 0;
	virtual void Unbind() = 0;
};
