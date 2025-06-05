// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWSlot.generated.h"

class UBorder;
class UImage;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWSlot : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UBorder> Background;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

};
