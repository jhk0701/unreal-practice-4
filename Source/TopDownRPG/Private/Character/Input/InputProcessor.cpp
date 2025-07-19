// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Input/InputProcessor.h"
#include "TDRPGEnum.h"

#include "TopDownRPG/TopDownRPG.h"

#pragma region InputProcessor

void UInputProcessor::SetInterval()
{
	bIsInInterval = true;
	FTimerManager& Timer = GetWorld()->GetTimerManager();

	Timer.SetTimer(
		IntervalTimer,
		FTimerDelegate::CreateUObject(this, &UInputProcessor::ClearInterval),
		InputInterval,
		false);

}

#pragma endregion


#pragma region Normal

void UInputNormal::Process()
{
	if (bIsInInterval)
		return;

	SetInterval();

	OnInputProcessed.ExecuteIfBound(GetContext());
}

FSkillInputContext UInputNormal::GetContext()
{
	FSkillInputContext Context;
	Context.bProcessIsCompleted = true;

	return Context;
}

#pragma endregion


#pragma region Combo

UInputCombo::UInputCombo() : ComboCount(0) {}

bool UInputCombo::CheckIsEnable(TFunction<bool()> InPredicate)
{
	// 콤보 입력 시, 최초 입력 -> 스킬 시전
	if (ComboCount == 0)
		return InPredicate();

	// 최초 입력이 아닌 경우, 콤보 사용 중.
	// 최대 사용 횟수 체크
	return ComboCount <= MaxCount;
}

void UInputCombo::Process()
{
	if (bIsInInterval)
		return;

	SetInterval();

	// 입력 이벤트 발행
	OnInputProcessed.ExecuteIfBound(GetContext());

	// 초기화 타이머
	FTimerManager& Timer = GetWorld()->GetTimerManager();

	// 지속 입력 시, 초기화하고 타이머 세팅
	if (Timer.IsTimerActive(ComboTimer))
		Timer.ClearTimer(ComboTimer);

	Timer.SetTimer(
		ComboTimer,
		FTimerDelegate::CreateUObject(this, &UInputCombo::Clear),
		ComboResetSec,
		false);
}

FSkillInputContext UInputCombo::GetContext()
{
	FSkillInputContext Context;
	Context.Count = ComboCount++; // 콤보 입력 횟수 증가
	Context.bProcessIsCompleted = true;

	return Context;
}

#pragma endregion


#pragma region Holding

UInputHolding::UInputHolding()
	: HoldingTime(8.0f),
	ElapsedTime(.0f), 
	Procedure(EInputProcedure::Ready)
{}

void UInputHolding::Process()
{
	if (bIsInInterval)
		return;

	if (Procedure != EInputProcedure::Ready)
		return;

	Procedure = EInputProcedure::InProgress;

	SetInterval();
	StartHoldTimer(.0f);

	OnInputProcessed.ExecuteIfBound(GetContext());
}

void UInputHolding::Complete()
{
	if (Procedure != EInputProcedure::InProgress)
		return;

	auto& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(HoldTimer))
		TimerManager.ClearTimer(HoldTimer);

	OnInputCompleted.ExecuteIfBound(GetContext());

	Procedure = EInputProcedure::Ready;
}

void UInputHolding::StartHoldTimer(float InElapsedTime)
{
	ElapsedTime = InElapsedTime;

	auto& TimerManager = GetWorld()->GetTimerManager();
	
	if (TimerManager.IsTimerActive(HoldTimer))
		TimerManager.ClearTimer(HoldTimer);

	TimerManager.SetTimer(
		HoldTimer, 
		[&]()
		{
			if (ElapsedTime + .1f > HoldingTime)
				Complete();
			else
				StartHoldTimer(ElapsedTime + .1f);
		}, 
		0.1f, 
		false);
}

FSkillInputContext UInputHolding::GetContext()
{
	FSkillInputContext Context;
	Context.bProcessIsCompleted = true;
	Context.bPlayAttackLast = false;
	Context.Percent = ElapsedTime / HoldingTime * 100.0f;

	return Context;
}

#pragma endregion


#pragma region Casting

FSkillInputContext UInputCasting::GetContext()
{
	FSkillInputContext Context;
	Context.bProcessIsCompleted = true;
	Context.bPlayAttackLast = true;
	Context.Percent = ElapsedTime / HoldingTime * 100.0f;

	return Context;
}

#pragma endregion


#pragma region Charging

UInputCharging::UInputCharging()
	: TargetTime(8.0f),
	Allowance(5.0f)
{
}

FSkillInputContext UInputCharging::GetContext()
{
	FSkillInputContext Context;
	Context.bProcessIsCompleted = true;
	Context.bPlayAttackLast = true;
	Context.Percent = ElapsedTime / HoldingTime * 100.0f;

	float TargetPer = ElapsedTime / TargetTime * 100.0f - 100.0f;
	Context.bChargeComplete = abs(TargetPer) < Allowance;

	return Context;
}

#pragma endregion


UInputProcessor* FInputProcessorFactory::GetInstance(ESkillInput InType, UObject* InOwner)
{
	switch (InType)
	{
	case ESkillInput::Normal:
		return NewObject<UInputNormal>(InOwner, UInputNormal::StaticClass());
	case ESkillInput::Combo:
		return NewObject<UInputCombo>(InOwner, UInputCombo::StaticClass());
	case ESkillInput::Holding:
		return NewObject<UInputHolding>(InOwner, UInputHolding::StaticClass());
	case ESkillInput::Charging:
		return NewObject<UInputCharging>(InOwner, UInputCharging::StaticClass());
	case ESkillInput::Casting:
		return NewObject<UInputCasting>(InOwner, UInputCasting::StaticClass());
	case ESkillInput::Area:
		return NewObject<UInputArea>(InOwner, UInputArea::StaticClass());
	default:
		return NewObject<UInputNormal>(InOwner, UInputNormal::StaticClass());
	}
}