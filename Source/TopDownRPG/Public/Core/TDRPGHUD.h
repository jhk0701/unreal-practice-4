// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TDRPGHUD.generated.h"

class UUIConfig;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATDRPGHUD : public AHUD
{
	GENERATED_BODY()

protected:
	// 특정 HUD가 관리할 UI 모음집
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TObjectPtr<UUIConfig> CommonUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TArray<TObjectPtr<UUIConfig>> Configs;

public:
	// 씬에 들어오면 UI 초기화
	void BeginPlay() override;
	virtual void Initialize();

};
