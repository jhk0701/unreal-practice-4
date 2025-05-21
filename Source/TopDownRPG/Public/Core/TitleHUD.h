// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATitleHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TMap<FName, class UTDRPGUserWidget*> uiMap;
	
	UPROPERTY()
	FString basePath;

public:
	ATitleHUD();
	virtual void BeginPlay() override;

	void Initialize();
};
