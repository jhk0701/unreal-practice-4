// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Updatable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUpdatable : public UInterface
{
	GENERATED_BODY()
};

class TOPDOWNRPG_API IUpdatable
{
	GENERATED_BODY()

public:
	virtual void Update(float DeltaTime) = 0;
};
