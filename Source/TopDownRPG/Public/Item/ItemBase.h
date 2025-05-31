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
	// 일반 C++과 달리 Unreal 객체들은 CDO를 통해 인스턴스화 됨
	// 그러므로 일반적으로 순수가상함수를 작성할 순 없음
	// 순수가상함수 선언을 위해선 PURE_VIRTUAL 매크로 사용
	// PURE_VIRTUAL(함수 시그니쳐, return type ;)
	virtual void Init(FItemDataRow& InData) PURE_VIRTUAL(UItemBase::Init, ;);

protected:
	FItemDataRow* Data = nullptr;
};
