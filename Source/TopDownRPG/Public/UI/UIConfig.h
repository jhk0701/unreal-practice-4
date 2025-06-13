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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ElementID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UTDRPGUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Position;

	/*
	// 사이즈 조절은 이번 프로젝트에선 필요없음
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Size;
	*/
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
