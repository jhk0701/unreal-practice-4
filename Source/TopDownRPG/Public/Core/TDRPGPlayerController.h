// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDRPGPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATDRPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Action")
	TObjectPtr<UInputAction> ClickAction;


public:
	virtual void BeginPlay() override;
	
};
