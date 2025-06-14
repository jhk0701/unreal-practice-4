// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIConfig.generated.h"


class UTDRPGUserWidget;

USTRUCT(BlueprintType)
struct FUIElementData 
{
	GENERATED_BODY()
	
	/*
	// Type 명칭으로 맵핑시도
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ElementID; 
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UTDRPGUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanOpenOnInit;
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FUIElementData> Elements;
};
