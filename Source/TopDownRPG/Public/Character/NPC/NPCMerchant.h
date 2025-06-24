// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NPC/TDRPGNPCBase.h"
#include "NPCMerchant.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ANPCMerchant : public ATDRPGNPCBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCData")
	FString MerchantID;

public:
	ANPCMerchant();
	virtual void BeginPlay() override;
	virtual void Interact() override;
};
