// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDRPGUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void Open();
	UFUNCTION()
	virtual void Close();
	UFUNCTION()
	virtual void Toggle();
};
