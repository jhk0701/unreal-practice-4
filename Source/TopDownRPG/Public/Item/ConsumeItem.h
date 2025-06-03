// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "ConsumeItem.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TOPDOWNRPG_API UConsumeItem : public UItemBase
{
	GENERATED_BODY()

public:
	virtual void Use();
	virtual void OnDurationEnded() PURE_VIRTUAL(UConsumeItem::OnDurationEnded, );
};
