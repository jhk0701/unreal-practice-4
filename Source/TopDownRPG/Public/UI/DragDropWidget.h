// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDropWidget.generated.h"

class UTDRPGUserWidget;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UDragDropWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UDragDropWidget();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UTDRPGUserWidget> DraggedWidget;
};
