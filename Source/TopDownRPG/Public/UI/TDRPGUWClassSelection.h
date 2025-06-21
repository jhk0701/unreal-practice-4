// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDRPGUserWidget.h"
#include "TDRPGUWClassSelection.generated.h"

class UButton;
class UTextBlock;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UTDRPGUWClassSelection : public UTDRPGUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta=(BindWidget))
	TObjectPtr<UButton> NextButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> ClassLabel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UTextBlock> ClassDescLabel;

	// TODO : 클래스 버튼 동적 생성
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UVerticalBox> ClassList;

	// TODO : 임시 클래스 버튼 제거
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIElement", meta = (BindWidget))
	TObjectPtr<UButton> TempClassButton;


public:
	void InitClassList();
};
