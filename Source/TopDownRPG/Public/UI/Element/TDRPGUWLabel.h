// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWLabel.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWLabel : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> Icon;
	
};
