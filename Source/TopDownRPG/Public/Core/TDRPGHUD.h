// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TDRPGHUD.generated.h"

class UUIConfig;
class UTDRPGUWCanvas;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATDRPGHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI");
	TSubclassOf<UTDRPGUWCanvas> CanvasFactory;

	// 특정 HUD가 관리할 UI 모음집
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TObjectPtr<UUIConfig> CommonUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TArray<TObjectPtr<UUIConfig>> Configs;

protected:
	virtual void PostInitializeComponents() override;
	virtual void InitHUD();

};
