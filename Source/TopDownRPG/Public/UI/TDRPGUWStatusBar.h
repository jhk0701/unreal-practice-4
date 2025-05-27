// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWStatusBar.generated.h"

class ATDRPGPlayer;
class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWStatusBar : public UTDRPGUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<ATDRPGPlayer> player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UProgressBar> ManaBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIElement, meta = (BindWidget))
	TObjectPtr<UTextBlock> ManaLabel;

public:
	void InitStatusBar(ATDRPGPlayer* NewPlayer);
	void OnHpChanged(uint32 Max, uint32 Current);
	void OnMpChanged(uint32 Max, uint32 Current);
};
