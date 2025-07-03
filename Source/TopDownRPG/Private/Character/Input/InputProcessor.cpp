// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Input/InputProcessor.h"
#include "TDRPGEnum.h"

#include "TopDownRPG/TopDownRPG.h"


#pragma region Normal

void UInputNormal::Process()
{
	FSkillInputContext Context;
	Context.bProcessIsCompleted = true;

	OnInputProcessed.ExecuteIfBound(Context);
}

#pragma endregion


#pragma region Combo

UInputCombo::UInputCombo()
	: ComboCount(0)
{
}

void UInputCombo::Process()
{
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


#pragma region Casting

UInputCasting::UInputCasting()
	: CurrentProcess(EInputProcedure::Ready),
	CastingTime(2.0f),
	ElapsedTime(0.0f)
{}

void UInputCasting::Process()
{
	if (CurrentProcess == EInputProcedure::InProgress)
		return;

	if (CurrentProcess == EInputProcedure::Ready)
		Start();
}

void UInputCasting::Start()
{
	CurrentProcess = EInputProcedure::InProgress;
	ElapsedTime = 0.0f;

	auto& Timer = GetWorld()->GetTimerManager();
	
	if (Timer.IsTimerActive(CastingTimer))
		Timer.ClearTimer(CastingTimer);

	Timer.SetTimer(
		CastingTimer, 
		FTimerDelegate::CreateUObject(this, &UInputCasting::Pressing), 
		0.1f, 
		true);
}

void UInputCasting::Pressing()
{
	ElapsedTime += 0.1f;

	if (ElapsedTime >= CastingTime)
	{
		// 입력 완료 처리
		FSkillInputContext Context;
		Context.bProcessIsCompleted = true;

		// 입력 이벤트 발행
		OnInputProcessed.ExecuteIfBound(Context);

		Release();
	}
}

void UInputCasting::Release()
{
	CurrentProcess = EInputProcedure::Ready;

	auto& Timer = GetWorld()->GetTimerManager();

	if (Timer.IsTimerActive(CastingTimer))
		Timer.ClearTimer(CastingTimer);
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
