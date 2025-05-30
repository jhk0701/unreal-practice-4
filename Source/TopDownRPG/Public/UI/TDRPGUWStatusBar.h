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
	
public:

	void InitStatusBar(TWeakObjectPtr<ATDRPGPlayer> NewPlayer);
	void OnHpChanged(uint32 Max, uint32 Current);
	void OnMpChanged(uint32 Max, uint32 Current);

protected:
	TWeakObjectPtr<ATDRPGPlayer> player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusBar, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusBar, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusBar, meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusBar, meta = (BindWidget))
	TObjectPtr<UProgressBar> ManaBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusBar, meta = (BindWidget))
	TObjectPtr<UTextBlock> ManaLabel;

};
