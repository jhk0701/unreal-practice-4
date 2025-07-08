// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWStatusWindow.generated.h"

enum class EStatus : uint8;
enum class EAbility : uint8;

class UPlayerManager;
class UCharacterData;

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWStatusWindow : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameLabel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ClassLabel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LvLabel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ExpLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HpLabel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MpLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StrLabel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DexLabel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> IntLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AtkLabel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DefLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

protected:
	UPlayerManager* BindedPlayer;

public:
	virtual void NativeOnInitialized() override;
	virtual void Open() override;

	void Bind(UPlayerManager* InPlayer);
	void Refresh();

private:
	void GetStatusText(UCharacterData* InCharData, EStatus InType, FText& OutText);
	void GetAbilityText(UCharacterData* InCharData, EAbility InType, FText& OutText);
};
