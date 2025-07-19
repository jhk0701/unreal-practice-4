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
	bool bProcessIsCompleted;
	int32 Count;
	float Percent;
	FVector Position;
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
	FSkillInputEvent OnInputStarted;
	FSkillInputEvent OnInputProcessed;
	FSkillInputEvent OnInputCompleted;

	virtual bool CheckIsEnable(TFunction<bool()> InPredicate) { return InPredicate(); };
	virtual void Process() {};
	virtual void Complete() {};

protected:
	bool bIsInInterval = false; 
	float InputInterval = 0.7;
	FTimerHandle IntervalTimer;

	void SetInterval();
	inline void ClearInterval() { bIsInInterval = false; };
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
	int32 MaxCount = 8; // TODO : 데이터에서 받아오기
	const float ComboResetSec = 2.0f;
	FTimerHandle ComboTimer;

	inline void Clear() { ComboCount = 0; };
};


UCLASS()
class TOPDOWNRPG_API UInputHolding : public UInputProcessor
{
	GENERATED_BODY()

public:
	UInputHolding();

	virtual void Process() override;
	virtual void Complete() override;

protected:
	// 현재 동작 상태
	EInputProcedure Procedure;

	// 홀딩 시간 세기
	float TargetTime = .0f;
	float ElapsedTime = .0f;
	FTimerHandle HoldTimer;

	void StartHoldTimer(float InElapsedTime);
};

// 계속 누르고 있다가 특정 지점에서 떼면 스킬 발동
UCLASS()
class TOPDOWNRPG_API UInputCharging : public UInputHolding
{
	GENERATED_BODY()

};


// 스킬 시전 동안 계속 누르기
UCLASS()
class TOPDOWNRPG_API UInputCasting : public UInputHolding
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