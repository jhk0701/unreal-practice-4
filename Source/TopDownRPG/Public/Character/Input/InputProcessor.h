// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputProcessor.generated.h"

enum class ESkillInput :uint8;

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FSkillInputContext
{
	GENERATED_BODY()

public:
	int32 InputCount;
	FVector InputPosition;
};

DECLARE_DELEGATE_OneParam(FSkillInputEvent, const FSkillInputContext&);


/**
 * 스킬 입력 동작 처리 클래스
 */
UCLASS(Abstract)
class TOPDOWNRPG_API UInputProcessor : public UObject
{
	GENERATED_BODY()

public:
	FSkillInputEvent OnInputProcessed;

	virtual void Process() {};
};

/// <summary>
/// 일반 입력
/// </summary>
UCLASS()
class TOPDOWNRPG_API UInputNormal : public UInputProcessor
{
	GENERATED_BODY()

public:
	void Process() override;
};

/// <summary>
/// 연속 입력
/// </summary>
UCLASS()
class TOPDOWNRPG_API UInputCombo : public UInputProcessor
{
	GENERATED_BODY()

public:
	void Process() override;

private:
	int32 ComboCount = 0;
	float ComboResetSec = 1.0f;
	FTimerHandle ComboTimer;

	inline void Clear() { ComboCount = 0; };
};

/// <summary>
/// 스킬 시전 동안 계속 누르기
/// </summary>
UCLASS()
class TOPDOWNRPG_API UInputCasting : public UInputProcessor
{
	GENERATED_BODY()

public:
	void Process() override;
	void Release();
};

/// <summary>
/// 계속 누르고 있다가 특정 지점에서 떼면 스킬 발동
/// </summary>
UCLASS()
class TOPDOWNRPG_API UInputCharging : public UInputProcessor
{
	GENERATED_BODY()

};

/// <summary>
/// 시전 시, 영역을 표시기가 보이고 해당 영역을 클릭하면 발동
/// </summary>
UCLASS()
class TOPDOWNRPG_API UInputArea : public UInputProcessor
{
	GENERATED_BODY()

	// 클릭 연계 필요

};

class TOPDOWNRPG_API FInputProcessorFactory
{
public:	
	static UInputProcessor* GetInstance(ESkillInput InType, UObject* InOwner);
};