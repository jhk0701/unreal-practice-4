// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWInputPlayerName.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWInputPlayerName : public UTDRPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> NameInputField;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CompleteButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackButton;

};
