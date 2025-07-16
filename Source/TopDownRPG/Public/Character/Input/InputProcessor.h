// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputProcessor.generated.h"

enum class ESkillInput : uint8;
enum class EInputProcedure : uint8;

USTRUCT(BlueprintType)
struct TOPDOWNRPG_API FSkillInputContext
{
	GENERATED_BODY()

public:
	int32 Count;
	float Percent;
	FVector Position;
	
	bool bProcessIsCompleted;
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

	virtual bool CheckIsEnable(TFunction<bool()> InPredicate) { return InPredicate(); };
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
	UInputCombo();
	virtual bool CheckIsEnable(TFunction<bool()> InPredicate) override;
	virtual void Process() override;

private:
	int32 ComboCount = 0;
	const float ComboResetSec = 1.0f;
	FTimerHandle ComboTimer;

	inline void Clear() { ComboCount = 0; };
};


UCLASS(Abstract)
class TOPDOWNRPG_API UInputHolding : public UInputProcessor
{
	GENERATED_BODY()

public:
	UInputHolding();
	virtual void Process() override;
	virtual void Release();

	inline void SetTargetTime(float InTime) { TargetTime = InTime; }

protected:
	float TargetTime;
	float ElapsedTime;
	EInputProcedure CurrentProcess;
	FTimerHandle ProcessTimer;

	virtual void Start();
	virtual void Pressing() {};
};

/// <summary>
/// 계속 누르고 있다가 특정 지점에서 떼면 스킬 발동
/// </summary>
UCLASS()
class TOPDOWNRPG_API UInputCharging : public UInputHolding
{
	GENERATED_BODY()

public:
	virtual void Release() override;

protected:
	virtual void Pressing() override;
};


/// <summary>
/// 스킬 시전 동안 계속 누르기
/// </summary>
UCLASS()
class TOPDOWNRPG_API UInputCasting : public UInputHolding
{
	GENERATED_BODY()

protected:
	virtual void Pressing() override;
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