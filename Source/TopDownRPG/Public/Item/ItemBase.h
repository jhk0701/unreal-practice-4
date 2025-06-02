// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

struct FItemDataRow;

// 아이템의 경우 추상클래스로 선언
// 추상클래스로 선언하기 위해 Abstract 특정자 사용
UCLASS(Abstract)
class TOPDOWNRPG_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	inline virtual void Init(FItemDataRow& InData) { Data = &InData; };

protected:
	FItemDataRow* Data = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	int32 Count;
};
