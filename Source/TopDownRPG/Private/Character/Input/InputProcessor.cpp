// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Input/InputProcessor.h"
#include "TDRPGEnum.h"

void UInputNormal::Process()
{
	FSkillInputContext Context;
	OnInputProcessed.ExecuteIfBound(Context);
}

void UInputCombo::Process()
{
	// 입력 처리
	FSkillInputContext Context;
	
	ComboCount++; // 콤보 입력 횟수 증가

	Context.InputCount = ComboCount;
	
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

void UInputCasting::Process()
{
}

void UInputCasting::Release()
{
}



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
