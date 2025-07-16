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

	FSkillInputContext Context;
	Context.bProcessIsCompleted = true;

	OnInputProcessed.ExecuteIfBound(Context);
}

#pragma endregion


#pragma region Combo

UInputCombo::UInputCombo() : ComboCount(0)
{}

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

	// 입력 처리
	FSkillInputContext Context;
	Context.Count = ++ComboCount; // 콤보 입력 횟수 증가
	Context.bProcessIsCompleted = true;

	// 입력 이벤트 발행
	OnInputProcessed.ExecuteIfBound(Context);

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

#pragma endregion


#pragma region Holding

UInputHolding::UInputHolding()
	: CurrentProcess(EInputProcedure::Ready),
	TargetTime(2.0f),
	ElapsedTime(0.0f)
{}

void UInputHolding::Process()
{
	if (CurrentProcess == EInputProcedure::InProgress)
		return;

	if (CurrentProcess == EInputProcedure::Ready)
		Start();
}

void UInputHolding::Start()
{
	CurrentProcess = EInputProcedure::InProgress;
	ElapsedTime = 0.0f;

	auto& Timer = GetWorld()->GetTimerManager();

	if (Timer.IsTimerActive(ProcessTimer))
		Timer.ClearTimer(ProcessTimer);

	Timer.SetTimer(
		ProcessTimer,
		FTimerDelegate::CreateUObject(this, &UInputHolding::Pressing),
		0.1f,
		true);
}

void UInputHolding::Release()
{
	CurrentProcess = EInputProcedure::Ready;

	auto& Timer = GetWorld()->GetTimerManager();

	if (Timer.IsTimerActive(ProcessTimer))
		Timer.ClearTimer(ProcessTimer);
}

#pragma endregion

#pragma region Charging

void UInputCharging::Release()
{
	// 입력 완료 처리
	FSkillInputContext Context;
	Context.Percent = ElapsedTime / TargetTime * 100.f;
	Context.bProcessIsCompleted = true;

	// 입력 이벤트 발행
	OnInputProcessed.ExecuteIfBound(Context);

	Super::Release();
}

void UInputCharging::Pressing()
{
	ElapsedTime += 0.1f;

	if (ElapsedTime >= TargetTime)
		Release();
}

#pragma endregion


#pragma region Casting

void UInputCasting::Pressing()
{
	ElapsedTime += 0.1f;

	if (ElapsedTime >= TargetTime)
	{
		// 입력 완료 처리
		FSkillInputContext Context;
		Context.Percent = ElapsedTime / TargetTime * 100.f;
		Context.bProcessIsCompleted = true;

		// 입력 이벤트 발행
		OnInputProcessed.ExecuteIfBound(Context);

		Release();
	}
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
	case ESkillInput::Casting:
		return NewObject<UInputCasting>(InOwner, UInputCasting::StaticClass());
	case ESkillInput::Charging:
		return NewObject<UInputCharging>(InOwner, UInputCharging::StaticClass());
	case ESkillInput::Area:
		return NewObject<UInputArea>(InOwner, UInputArea::StaticClass());
	default:
		return NewObject<UInputNormal>(InOwner, UInputNormal::StaticClass());
	}
}
